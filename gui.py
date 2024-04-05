import matplotlib.pyplot as plt
from wordcloud import WordCloud, STOPWORDS
import os

# Function to generate word cloud for a file
def generate_word_cloud(file_path):
    # Read text from file
    with open(file_path, mode='r', encoding='utf-8') as file:
        text = file.read()

    # Generate word cloud
    stopwords = set(STOPWORDS)
    wc = WordCloud(
        background_color='white',
        stopwords=stopwords,
        height=600,
        width=400
    )
    wc.generate(text)

    # Display the word cloud
    plt.imshow(wc, interpolation='bilinear')
    plt.axis('off')
    plt.show()

# Main function
def main():
    # Get the number of files from the user
    N = int(input("Enter the number of files: "))
    file_paths = []

    # Get the file paths from the user
    for i in range(N):
        file_path = input(f"Enter the path for file {i + 1}: ")
        if os.path.exists(file_path):
            file_paths.append(file_path)
        else:
            print(f"File {file_path} doesn't exist.")

    # Generate word clouds for each file
    for file_path in file_paths:
        print(f"Generating word cloud for {file_path}")
        generate_word_cloud(file_path)

if __name__ == "_main_":
    main()