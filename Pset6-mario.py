from cs50 import get_int

# Prompt user for height repeatedly until a valid number between 1 and 8 is entered
while True:
    height = get_int("Enter height from 1 to 8 to build pyramid: ")
    if height >= 1 and height <= 8:
        break

# Loop through each level (row) of the pyramid
for h in range(height):

    # Loop through each column in the current row
    for w in range(height):
        # Print spaces to align the pyramid to the right
        if w < height - h - 1:
            print(f" ", end="")
        # Print hashes for the pyramid
        else:
            print("#", end="")

    # Move to the next line after completing the current row
    print()
