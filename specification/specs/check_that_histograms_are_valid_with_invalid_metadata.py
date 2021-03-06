from tthAnalysis.HiggsToTauTau.jobTools import run_cmd
from config import config

def check_that_histograms_are_valid_with_invalid_metadata():

    # Prepare

    histogram_with_invalid_metadata = "%(fixtures_dir)s/histogram_with_invalid_metadata.root" % config

    histograms = [
        "%(fixtures_dir)s/histogram_1.root" % config,
        histogram_with_invalid_metadata
    ]

    # Run task

    command = 'python %(scripts_dir)s/check_that_histograms_are_valid.py' % config
    command_arguments = " ".join(histograms)
    command_with_arguments = command + " " + command_arguments + "; echo EXIT_STATUS_WAS: $?;"

    command_output = run_cmd(command_with_arguments)

    # Check result
    expected_error_message = 'ERROR: real metadata does not match expected metadata for histogram: %s' % histogram_with_invalid_metadata
    if command_output.find(expected_error_message) == -1:
        print('Output must contain information that metadata does not match')
        return False

    if command_output.find('EXIT_STATUS_WAS: 1') == -1:
        print('Exit status must be 1 if metadata does not match')
        return False

    return True
