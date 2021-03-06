import os

class ClusterHistogramAggregator:

    def __init__(
        self,
        input_histograms=None,
        final_output_histogram=None,
        maximum_histograms_in_batch=20,
        waitForJobs = True,
        sbatch_manager=None,
        auxDirName = None,
    ):
        self.input_histograms = input_histograms
        self.final_output_histogram = final_output_histogram
        self.sbatch_manager = sbatch_manager
        self.maximum_histograms_in_batch = maximum_histograms_in_batch
        self.waitForJobs = waitForJobs
        self.auxDirName = auxDirName

    def create_output_histogram(
        self
    ):
        self.aggregate(
            input_histograms=self.input_histograms,
            final_output_histogram=self.final_output_histogram,
            maximum_histograms_in_batch=self.maximum_histograms_in_batch
        )

    def aggregate(
        self,
        input_histograms=None,
        final_output_histogram=None,
        maximum_histograms_in_batch=20,
        level=0
    ):

        # Log some info

        print("ClusterHistogramAggregator#aggregate(%s, %s, %s, %s)" % (
            input_histograms,
            final_output_histogram,
            maximum_histograms_in_batch,
            level
        ))

        # Create jobs for output files

        output_histograms = []
        current_job_id = 0

        while current_job_id * maximum_histograms_in_batch < len(input_histograms):
            start_pos = current_job_id * maximum_histograms_in_batch
            end_pos = start_pos + maximum_histograms_in_batch
            output_histogram = final_output_histogram.replace(
                ".root",
                "_%s-%s.root" % (level, current_job_id)
            )
            output_histograms.append(output_histogram)

            self.hadd_on_cluster_node(
                input_histograms=input_histograms[start_pos:end_pos],
                output_histogram=output_histogram
            )

            current_job_id = current_job_id + 1

        self.sbatch_manager.waitForJobs()

        # Aggregate output files

        if len(output_histograms) > maximum_histograms_in_batch:

            # Recursive call to method self

            self.aggregate(
                input_histograms=output_histograms,
                final_output_histogram=final_output_histogram,
                maximum_histograms_in_batch=maximum_histograms_in_batch,
                level=level + 1
            )

        else:

            # This is the last aggregation

            self.hadd_on_cluster_node(
                input_histograms=output_histograms,
                output_histogram=final_output_histogram
            )

            if self.waitForJobs:
                self.sbatch_manager.waitForJobs()

        # Delete output files produced by "intermediate" levels

        # for output_histogram in output_histograms:
        #    os.remove(output_histogram)

        return True

    def hadd_on_cluster_node(
        self,
        input_histograms=None,
        output_histogram=None,
    ):

        output_dir = self.auxDirName if self.auxDirName else os.path.dirname(output_histogram)

        print("ClusterHistogramAggregator#hadd_on_cluster_node(input_histograms=%s, output_histogram=%s, output_dir=%s)" % (
            input_histograms, output_histogram, output_dir))

        if not (input_histograms and output_histogram and output_dir):
            raise ValueError(
                'SBatchManager#hadd_on_cluster_node: All parameters not defined.')

        bash_command_template = '''

            # Load vars

            export SCRIPTS_DIR="$CMSSW_BASE/src/tthAnalysis/HiggsToTauTau/scripts"
            export SCRATCHED_INPUT_HISTOGRAMS=""
            export INPUT_HISTOGRAMS="{input_histograms}"
            export OUTPUT_HISTOGRAM="{output_histogram}"
            echo "Input histograms are: $INPUT_HISTOGRAMS, Output histogram is: $OUTPUT_HISTOGRAM"


            # Check that input histograms are ok on /home

            python $SCRIPTS_DIR/check_that_histograms_are_valid.py $INPUT_HISTOGRAMS
            check_that_histograms_are_valid_exit_status=$?

            if [[ $check_that_histograms_are_valid_exit_status -ne 0 ]]; then
              echo 'ERROR Some of the input histograms are not valid. Will stop execution.'
              return 1
            fi


            # Create scratch dir for output root

            export SCRATCHED_OUTPUT_HISTOGRAM="$SCRATCH_DIR/{output_histogram}"
            export SCRATCHED_OUTPUT_HISTOGRAM_DIRECTORY="`dirname $SCRATCHED_OUTPUT_HISTOGRAM`"
            echo "SCRATCHED_OUTPUT_HISTOGRAM: $SCRATCHED_OUTPUT_HISTOGRAM"
            echo "SCRATCHED_OUTPUT_HISTOGRAM_DIRECTORY: $SCRATCHED_OUTPUT_HISTOGRAM_DIRECTORY"

            echo "Create scratch dir for output root: mkdir -p $SCRATCHED_OUTPUT_HISTOGRAM_DIRECTORY"
            mkdir -p $SCRATCHED_OUTPUT_HISTOGRAM_DIRECTORY


            for INPUT_HISTOGRAM in $INPUT_HISTOGRAMS; do

                SCRATCHED_INPUT_HISTOGRAM="$SCRATCH_DIR/$INPUT_HISTOGRAM"
                SCRATCHED_INPUT_HISTOGRAM_DIRECTORY="`dirname $SCRATCHED_INPUT_HISTOGRAM`"
                echo "SCRATCHED_INPUT_HISTOGRAM: $SCRATCHED_INPUT_HISTOGRAM"
                echo "SCRATCHED_INPUT_HISTOGRAM_DIRECTORY: $SCRATCHED_INPUT_HISTOGRAM"

                echo "Create parent dir: mkdir -p $SCRATCHED_INPUT_HISTOGRAM_DIRECTORY"
                mkdir -p $SCRATCHED_INPUT_HISTOGRAM_DIRECTORY

                echo "Copy histogram and metadata to scratch: cp -a $INPUT_HISTOGRAM* $SCRATCHED_INPUT_HISTOGRAM_DIRECTORY"
                cp "$INPUT_HISTOGRAM"* "$SCRATCHED_INPUT_HISTOGRAM_DIRECTORY"

                export SCRATCHED_INPUT_HISTOGRAMS="$SCRATCHED_INPUT_HISTOGRAMS $SCRATCHED_INPUT_HISTOGRAM"
            done


            # Check that input histograms are valid

            python $SCRIPTS_DIR/check_that_histograms_are_valid.py $SCRATCHED_INPUT_HISTOGRAMS
            check_that_histograms_are_valid_exit_status=$?

            if [[ $check_that_histograms_are_valid_exit_status -ne 0 ]]; then
              echo 'ERROR Some of the input histograms are not valid. Will stop execution.'
              return 1
            fi


            # Hadd

            echo "Create a new histogram: hadd $SCRATCHED_OUTPUT_HISTOGRAM $SCRATCHED_INPUT_HISTOGRAMS"
            hadd $SCRATCHED_OUTPUT_HISTOGRAM $SCRATCHED_INPUT_HISTOGRAMS
            hadd_exit_status=$?

            if [[ $hadd_exit_status -ne 0 ]]; then
              echo 'ERROR hadd exited w/ non-zero return code. Will stop execution.'
              return 1
            fi


            # Create metadata file for output histogram on scratch

            python $SCRIPTS_DIR/create_histogram_metadata.py $SCRATCHED_OUTPUT_HISTOGRAM


            # Check that input histograms are equal to output histogram

            python $CMSSW_BASE/src/tthAnalysis/HiggsToTauTau/scripts/check_that_histograms_are_equal.py $SCRATCHED_OUTPUT_HISTOGRAM $SCRATCHED_INPUT_HISTOGRAMS
            check_that_histograms_are_equal_exit_status=$?

            if [[ $check_that_histograms_are_equal_exit_status -ne 0 ]]; then
              echo 'ERROR Input histograms do not equal output histogram. Will stop execution.'
              return 1
            fi


            # Store result in correct place

            OUTPUT_HISTOGRAM_DIRECTORY="`dirname $OUTPUT_HISTOGRAM`"
            echo "Make a directory for result root: mkdir -p $OUTPUT_HISTOGRAM_DIRECTORY"
            mkdir -p $OUTPUT_HISTOGRAM_DIRECTORY

            echo "Copy result from scratch to /home: cp $SCRATCHED_OUTPUT_HISTOGRAM* $OUTPUT_HISTOGRAM_DIRECTORY"
            cp "$SCRATCHED_OUTPUT_HISTOGRAM"* $OUTPUT_HISTOGRAM_DIRECTORY



            # Cleanup will be automatic

            echo "Cleanup will be automatic"
        '''

        bash_command = bash_command_template.format(
            input_histograms=" ".join(input_histograms),
            output_histogram=output_histogram
        )

        ##task_name = 'create_%s' % output_histogram.replace(
        ##    '/', '_').replace(' ', '_')
        task_name = 'create_%s' % os.path.basename(output_histogram)

        self.sbatch_manager.submit_job_version2(
            task_name=task_name,
            command=bash_command,
            output_dir=output_dir
        )
