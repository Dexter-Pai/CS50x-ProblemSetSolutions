import cs50


def main():
    input_string = (input("Input your text here : "))

    sentence_counter = 0
    word_counter = 0
    letter_counter = 0

    for words in input_string:
        if words == '.' or words == '?' or words == '!':
            sentence_counter += 1

    strings_words = []
    strings_words = input_string.split()
    word_counter = len(strings_words)

    # print(input_string)
    # print(strings_words)
    # print(word_counter)

    letters_list = []
    for letters in input_string:
        if not (letters == '.' or letters == ',' or
                letters == '?' or letters == ' ' or
                letters == '!' or letters == ':' or
                letters == ';' or letters == '\''):
            letters_list.append(letters.lower())

    letter_counter = len(letters_list)

    # print(letters_list)
    print(letter_counter)
    print(word_counter)
    print(sentence_counter)

    index = (0.0588 * average(letter_counter, word_counter)) - (0.296 * average(sentence_counter, word_counter)) - 15.8
    index = round(index)

    if index < 1:
        print("Before Grade 1")
    elif index > 16:
        print("Grade 16+")
    else:
        print(f"Grade {index}")


def letters(input):
    for i in len(input):
        print(i)


def average(a, b):
    return a * 100 / b


if __name__ == "__main__":
    main()