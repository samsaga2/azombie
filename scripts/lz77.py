import sys

def compress(values, verbose=True):
    out = []

    def equal_len(left, right):
        length = 0
        while left < right and right < len(values) and values[left] == values[right] and length < 255:
            length += 1
            left += 1
            right += 1
        return length

    def find_back_offset(current_index):
        max_back_offset = 0
        max_back_len = 0
        i = max(0,current_index-255)
        while i < current_index:
            back_len = equal_len(i, current_index)
            if back_len > max_back_len:
                max_back_len = back_len
                max_back_offset = current_index-i
            i += 1
        return (max_back_offset, max_back_len)

    i = 0
    size = 0
    while i < len(values):
        back_offset, back_len = find_back_offset(i)
        i += back_len
        next_char = values[i] if i < len(values) else 0
        if back_len==0:
            out.extend([back_len, next_char])
        else:
            out.extend([back_len, back_offset, next_char])
        i += 1
        size += 1
        if verbose:
            sys.stderr.write("compressing... %d%%\t\t\r" % (i/float(len(values))*100))
            sys.stderr.flush()

    if verbose:
        sys.stderr.write("original %s bytes -> final %s bytes\n" % (len(values), len(out)))

    return [size&0xff,size>>8] + out

def uncompress(data):
    out = []

    i = 2
    while i < len(data):
        back_len = data[i]
        i += 1
        if back_len != 0:
            back_offset = len(out)-data[i]
            i += 1
            while back_len > 0:
                out.append(out[back_offset])
                back_offset += 1
                back_len -= 1
        out.append(data[i])
        i += 1

    return out

if __name__ == "__main__":
    if sys.argv[1] == "c":
        with open(sys.argv[2], "rb") as f:
            sys.stdout.buffer.write(bytes(compress(f.read())))
    elif sys.argv[1] == "d":
        with open(sys.argv[2], "rb") as f:
            sys.stdout.buffer.write(bytes(uncompress(f.read())))
