// JavaScript code to read words from input file and update the word cloud
function updateWordCloud(words) {
    var wordCloudDiv = document.getElementById('wordCloud');
    wordCloudDiv.innerHTML = ''; // Clear existing content

    // Add each word to the word cloud
    words.forEach(function(word, index) {
        var span = document.createElement('span');
        span.textContent = word + ' ';
        span.className = 'word' + (index === 0 ? ' largest' : index === words.length - 1 ? ' smallest' : '');
        wordCloudDiv.appendChild(span);
    });
}

// Function to handle file input change event
function handleFileSelect(event) {
    var file = event.target.files[0];
    var reader = new FileReader();

    reader.onload = function(event) {
        var words = event.target.result.split(/\s+/); // Split words by whitespace
        updateWordCloud(words);
    };

    reader.readAsText(file);
}

// Attach event listener to file input element
document.getElementById('fileInput').addEventListener('change', handleFileSelect);
