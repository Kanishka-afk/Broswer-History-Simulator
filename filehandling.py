
with open("numbers.txt", "r") as f:
    numbers = f.read().split()

with open("numbers.txt", "w") as f:
    for num in numbers:
        n = int(num)
        total = 0
        power = len(num)

        while n > 0:
            digit = n % 10
            total = total + digit ** power
            n = n // 10

        if total == n:
            f.write(str(n) + " is an Armstrong number\n")
        else:
            f.write(str(n) + " is not an Armstrong number\n")

print("Result written to file")