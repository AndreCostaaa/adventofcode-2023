import os


def map_to_dict(line_arr, target_map):
    for line in line_arr:
        splitted = line.split(" ")
        qty = int(splitted[2])
        dst_range_start = int(splitted[0])
        src_range_start = int(splitted[1])

        for i in range(qty):
            target_map[src_range_start + i] = dst_range_start + i


def find_value_in_map(map, value):
    for line in map:
        splitted = line.split(" ")
        qty = int(splitted[2])
        dst_range_start = int(splitted[0])
        src_range_start = int(splitted[1])
        delta = value - src_range_start
        if delta >= 0 and delta <= qty:
            return dst_range_start + delta
    return value


def find_value_in_map_reverse(map, value):
    for line in map:
        splitted = line.split(" ")
        qty = int(splitted[2])
        dst_range_start = int(splitted[0])
        src_range_start = int(splitted[1])
        delta = value - dst_range_start
        if delta >= 0 and delta < qty:
            return src_range_start + delta

    return value


lines = []
with open(
    os.path.join(os.path.dirname(os.path.realpath(__file__)), "sample.txt"), "r"
) as f:
    lines = f.readlines()

seed_data = lines[0].split("seeds: ")[1].split(" ")


maps = []
on_map = False
for i, line in enumerate(lines[1:]):
    if ":" in line:
        on_map = True
        maps.append([])
        continue
    if line.isspace():
        on_map = False
        continue
    if on_map:
        maps[-1].append(line)

location_targets_map = sorted(maps[-1], key=lambda x: int(x.split(" ")[0]))

maps.pop()


def find():
    for location in range(1e8):
        value = find_value_in_map_reverse(location_targets_map, location)
        for map in reversed(maps):
            value = find_value_in_map_reverse(map, value)

        for i in range(0, len(seed_data), 2):
            delta = value - int(seed_data[i])
            if delta >= 0 and delta < int(seed_data[i + 1]):
                print(location)
                return


find()
