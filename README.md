


### Day 3 — Byte Frequency Analysis

- Implemented byte frequency counting using a 256-element array.
- Read input files byte by byte in binary mode.
- Converted bytes to unsigned values (0–255).
- Counted occurrences of each byte.
- Displayed frequencies of bytes present in the file.
- Calculated total bytes processed.

Concepts learned:
- ASCII values
- Unsigned bytes
- Frequency arrays
- Array indexing
- Binary file processing
- EOF and file stream behavior




### Day 5 — Huffman Tree Foundation

- Implemented a Huffman tree node.
- Added leaf and internal node creation.
- Implemented a min-priority queue.
- Built the Huffman tree from byte frequencies.
- Generated binary Huffman codes using tree traversal.
- Added recursive tree cleanup to free allocated memory.

Concepts learned:
- Binary trees
- Leaf and internal nodes
- Pointers
- Recursion
- Priority queues
- Min-heaps
- Huffman coding

### Day 6 — Huffman Code Generation & Encoding

oal: Generate Huffman binary codes from the Huffman tree and encode the input file.

Implemented
- Generated Huffman codes using recursive tree traversal.
- Used `0` for left branches and `1` for right branches.
- Stored generated codes in a lookup table using `array<string, 256>`.
- Encoded the input file by replacing each byte with its corresponding Huffman code.
- Displayed the encoded bit sequence.
- Calculated the encoded size in bits.
- Calculated compression ratio and percentage of space saved.

Concepts Learned
- Recursive tree traversal
- Huffman encoding
- Lookup tables
- Byte-to-code mapping
- Binary encoding
- Compression ratio
- Space savings calculation

Current Progress
The program can generate Huffman codes and encode the input into a bit string in memory.

NOTE: The encoded data is currently represented as a string of `0` and `1`. Writing the compressed data into a binary output file will be implemented in a future stage.




