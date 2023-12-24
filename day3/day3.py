from os import path
import os
from dataclasses import dataclass
@dataclass
class Number:
    number:int
    x: int
    y: int

def parse_number(lines:list[list[str]],row,col):
    if not is_number_at(lines, row, col):
        raise RuntimeError()
    start_index = 0
    end_index = len(lines[row]) -1
    for j in range(col,-1,-1):
        if not lines[row][j].isdigit():
            start_index = j +1
            break
    for j in range(col,len(lines[row])):
        if not lines[row][j].isdigit():
            end_index = j -1
            break
        
    return Number(number= int(lines[row][start_index:end_index+1]),x=start_index, y=row)

def is_number_at(lines:list[list[str]], i,j):
    if i < 0 or i >= len(lines):
        return False
    if j < 0 or j>= len(lines[i]):
        return False
    
    return lines[i][j].isdigit()

def main():

    lines = []
    with open(path.join(os.path.dirname(os.path.abspath(__file__)),"sample.txt"),"r") as f:
        lines = f.readlines()

    numbers = []
    sum = 0
    for i, line in enumerate(lines):
        for j, c in enumerate(line):
            if c.isdigit() or c == '.' or c.isspace():
                continue
            print(c)
            for row in range(i-1,i+2):
                for col in range(j-1, j+2):
                    if not is_number_at(lines, row,col):
                        continue
                    number = parse_number(lines,row, col)
                    already_found = False
                    for num in numbers:
                        if num.x == number.x and num.y == number.y:
                            already_found = True
                            break
                    if not already_found:
                        numbers.append(number)
            if len(numbers) == 2:
                sum += numbers[0].number * numbers[1].number
            numbers = []       
    print(sum)
    #print(sum([n.number for n in numbers]))
     


if __name__ == "__main__":
    main()