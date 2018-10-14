import argparse
import re
import sys

from generate_file_from_template import run as generate

# @todo: Move to external config file + add destination paths
TEMPLATE_FILE_PATH_HEADER  = "../code/templates/Module/TEMPLATE.h"
TEMPLATE_FILE_PATH_PRIVATE = "../code/templates/Module/TEMPLATE_private.h"
TEMPLATE_FILE_PATH_SOURCE  = "../code/templates/Module/TEMPLATE.c"
TEMPLATE_FILE_PATH_CONFIG  = "../code/templates/Module/TEMPLATE_config.c"

# Main entry point
def main():
    name = get_name_from_args()
    if name == "":
        print("Invalid name. Please try again")
        sys.exit()
    # Generate the header file
    generate(name, TEMPLATE_FILE_PATH_HEADER)
    # Generate the private header file
    generate(name, TEMPLATE_FILE_PATH_PRIVATE)
    # Generate the source file
    generate(name, TEMPLATE_FILE_PATH_SOURCE)
    # Generate the config file
    generate(name, TEMPLATE_FILE_PATH_CONFIG)

# Return a valid name from command-line arguments
def get_name_from_args():
    # Create and use an ArgumentParser
    parser = argparse.ArgumentParser()
    parser.add_argument(
        "name",
        help="Name of the new class",
        metavar="name")
    args = parser.parse_args()
    name = args.name
    # Generate a "clean" name without special characters
    name_clean = re.sub(r'[`\=~!@#$%^&*()+\[\]{};\'\\:"|<,./<>?]', "_", name)
    if name_clean == name:
        # Original name was unchanged, return it
        return name
    else:
        # Original name was modified
        print("Given name \"%s\" is invalid!" % name)
        # Suggest the "clean" name as an alternative
        res = True if (input("Use \"%s\" instead? (y/n): " % name_clean).lower() == "y") else False 
        if res is True:
            # Return the clean name
            return name_clean
        else:
            # Return nothing
            return ""

# Call the main function
if __name__ == "__main__":
    main()
