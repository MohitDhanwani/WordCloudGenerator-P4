import matplotlib.pyplot as plt
from wordcloud import WordCloud, STOPWORDS
import os

def generate_word_cloud(file_path):
    
    with open(file_path, mode='r', encoding='utf-8') as file:
        text = file.read()

    
    stopwords = set(STOPWORDS)
    wc = WordCloud(
        background_color='white',
        stopwords=stopwords,
        height=600,
        width=400
    )
    wc.generate(text)

   
    plt.imshow(wc, interpolation='bilinear')
    plt.axis('off')
    plt.show()


def main():
    
    N = int(input("Enter the number of files: "))
    file_paths = []

    
    for i in range(N):
        file_path = input(f"Enter the path for file {i + 1}: ")
        if os.path.exists(file_path):
            file_paths.append(file_path)
        else:
            print(f"File {file_path} doesn't exist.")

    
    for file_path in file_paths:
        print(f"Generating word cloud for {file_path}")
        generate_word_cloud(file_path)

if __name__ == "__main__":
    main()