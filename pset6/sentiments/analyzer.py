from nltk.tokenize import TweetTokenizer

class Analyzer():
    """Implements sentiment analysis."""

    def __init__(self, positives, negatives):
        """Initialize Analyzer."""

        self.positives = set()
        self.negatives = set()

        with open(positives) as infile:
            for line in infile:
                if line[0] != ';' and line != '':
                    self.positives.add(line.strip())

        with open(negatives) as infile:
            for line in infile:
                if line[0] != ';' and line != '':
                    self.negatives.add(line.strip())

    def analyze(self, text):
        """Analyze text for sentiment, returning its score."""

        tokenizer = TweetTokenizer()

        score = 0

        tweet = tokenizer.tokenize(text.lower())
        for word in tweet:
            if word in self.positives:
                score += 1
            if word in self.negatives:
                score -= 1

        return score
