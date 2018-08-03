import argparse
import os
import re
import sys

#
def run(name, template_file_path):
    print("name: %s" % name)
    print("path: %s" % template_file_path)

    # Get the raw template text
    template = get_template(template_file_path)

    # Fill the template with the given name
    filled_template = fill_template(template, name)
    
    # Generate the file name
    output_file_name = generate_file_name(name, template_file_path)
    print("out: %s" % output_file_name)
    # Generate the file
    generate_file(output_file_name, filled_template)


def generate_file(file_path, filled_template):
    with open(file_path, "w") as file:
        file.write(filled_template)


def generate_file_name(name, template_file_path):
    root, extension = os.path.splitext(template_file_path)
    return name + extension


def get_name_uppercase_underscore(name):
    # Convert camelcase to underscores
    s1 = re.sub("(.)([A-Z][a-z]+)", r"\1_\2", name)
    # Replace generated double underscores
    s2 = re.sub("(__)", "_", s1)
    # Finish the conversion and make it uppercase
    return re.sub("([a-z0-9])([A-Z])", r"\1_\2", s2).upper()


def fill_template(template, name):
    # Generate an uppercase name with underscores
    name_upper_und = get_name_uppercase_underscore(name)
    # Fill template with the new name
    filled = template.replace("NAME_AS_IS", name)
    return filled.replace("NAME_CAP_UND", name_upper_und)


def get_template(file_path):
    with open(file_path, "r") as file:
        return file.read()


if __name__ == "__main__":
    name, template_file_path = parse_args()
    run(name, template_file_path)
