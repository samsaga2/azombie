import sys

maze = [
    '##################',
    '# #   #          #',
    '# # # #      #   #',
    '# # # #      #   #',
    '# # #        #   #',
    '# # # ########   #',
    '#   # #          #',
    '##################'
    ]

start = (1,1)
end = (16,6)

def print_maze():
    for j in range(0, len(maze)):
        for i in range(0, len(maze[j])):
            if (i,j) == start:
                sys.stdout.write('S')
            elif (i,j) == end:
                sys.stdout.write('E')
            else:
                sys.stdout.write(maze[j][i])
        print("")

def clear_terminal():
    sys.stderr.write("\x1b[2J\x1b[H")

def calculate_distances():
    distances = []
    for j in range(0, len(maze)):
        distances.append([])
        for i in range(0, len(maze[j])):
            if maze[j][i] == '#':
                distances[j].append(65535)
            else:
                distances[j].append(0)

    def iterate_distance(x,y,len):
        distances[y][x] = len
        len=len+1
        if distances[y][x-1] == 0:
            iterate_distance(x-1,y,len)
        if distances[y][x+1] == 0:
            iterate_distance(x+1,y,len)
        if distances[y-1][x] == 0:
            iterate_distance(x,y-1,len)
        if distances[y+1][x] == 0:
            iterate_distance(x,y+1,len)

    x,y=end
    iterate_distance(x,y,1)

    return distances
    
def print_distances(distances):
    for j in range(0, len(maze)):
        for i in range(0, len(maze[j])):
            sys.stdout.write("{:>6}".format(distances[j][i]))
        print()

def move(distances):
    global start
    x, y = start
    left = distances[y][x-1]
    right = distances[y][x+1]
    top = distances[y-1][x]
    bottom = distances[y+1][x]
    print("Left {} right {} top {} bottom {}".format(left, right, top, bottom))
    if left < right and left < bottom and left < top:
        x = x - 1
    elif right < left and right < bottom and right < top:
        x = x + 1
    elif top < bottom:
        y = y - 1
    elif bottom < top:
        y = y + 1
    start = (x,y)

print_maze()
while start != end:
    distances = calculate_distances()
    print_distances(distances)
    input()
    move(distances)
    print_maze()
