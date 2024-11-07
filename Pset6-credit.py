
def main():
    while True:
        try:
            # Input the credit card number
            user_input = int(input("Number: "))
            if user_input > 0:
                break
        except ValueError:
            pass
        print("Please enter a valid positive number.")

    # Get the credit card number from user input
    credit_card_no = user_input

    arr = []
    count = 0

    # Extract the digits and store them in an array
    while credit_card_no != 0:
        remainder = credit_card_no % 10
        # Store digits in reverse order in the array
        arr.append(remainder)
        credit_card_no = credit_card_no // 10
        # Track the number of digits stored
        count += 1

    # Check if the credit card number length is valid
    if count < 13 or count > 16:
        print("INVALID")
        return

    sum = 0
    sum2 = 0
    finalsum = 0

    # Iterate through every second digit starting from second last digit
    for j in range(1, len(arr), 2):
        # If a two digit number
        if (arr[j] * 2) >= 10:
            # Sum individual digits of the number as well
            sum += (arr[j] * 2) % 10 + (arr[j] * 2) // 10
        else:
            sum += arr[j] * 2

    # Iterate through the remaining alternate digits starting from last
    for k in range(0, len(arr), 2):
        sum2 += arr[k]

    finalsum = sum + sum2

    # Check the validity of Luhn's algorithm
    if finalsum % 10 != 0:
        print("INVALID")
        return

    # Determine the card type based on the card's starting digits and length
    if arr[-1] == 3 and (arr[-2] == 4 or arr[-2] == 7) and count == 15:
        print("AMEX")
    elif arr[-1] == 5 and (arr[-2] in [1, 2, 3, 4, 5]) and count == 16:
        print("MASTERCARD")
    elif arr[-1] == 4 and count in [13, 16]:
        print("VISA")
    else:
        print("INVALID")


main()
