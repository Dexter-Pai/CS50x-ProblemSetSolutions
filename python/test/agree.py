s = input("Do you agree? (Y/N)\n")

s = s.lower()
if s in ['yes', 'y']:
    print("Agreed")
elif s in ['no', 'n']:
    print("Not agreed")