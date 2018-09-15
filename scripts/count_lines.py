from os      import path, walk
from sys     import argv

START_PATH = "."
PRINT_FILE_LIST = False

def main():
    file_list, path_list = get_file_list()
    print("File count: %u" % len(file_list))
    total_line_count = 0
    total_blank_count = 0
    for file in path_list:
        line_count, blank_count = get_line_count_in_file(file)
        total_line_count += line_count
        total_blank_count += blank_count
    print("Total line count: %u (%u)" % (total_line_count, total_blank_count))
    print("Used line percentage %.2f%%" % get_used_line_percentage(total_line_count, total_blank_count))

def get_file_list():
    file_list = []
    path_list = []
    for (dir_path, dir_names, file_names) in walk(START_PATH):
        file_paths = [path.join(dir_path, file_name).replace('\\','/') for file_name in file_names]
        file_list.extend(file_names)
        path_list.extend(file_paths)
    return file_list, path_list

def get_line_count_in_file(file):
    count = 0
    blank_count = 0
    for line in open(file):
        count += 1
        if line in ["\n", "\r\n"]:
            blank_count += 1

    if PRINT_FILE_LIST:
        print("%s: %u (%u)" % (file, count, blank_count))
    return count, blank_count

def get_used_line_percentage(line_count, blank_count):
    if line_count is 0:
        return 0.0
    else:
        return (100 *(1 - (blank_count / line_count)))

def print_list(list):
    print(*list, sep='\n')

# Call the main function
if __name__ == "__main__":
    START_PATH = argv[1]
    PRINT_FILE_LIST = (argv[2] == 1)
    main()

