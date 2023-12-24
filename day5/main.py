seeds = []

maps_arr = [{} for _ in range(7)]


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


lines = []
with open("sample.txt", "r") as f:
    lines = f.readlines()


seeds = [int(x) for x in lines[0].split("seeds: ")[1].split(" ")]

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

locations = []
for seed in seeds:
    value = seed
    for map in maps:
        value = find_value_in_map(map, value)

    locations.append(value)

print(min(locations))
