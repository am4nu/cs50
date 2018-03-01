import nltk
import helpers
import sys


class Analyzer():
    """Implements sentiment analysis."""

    def __init__(self, positives, negatives):
        """Initialize Analyzer."""
        self.positive = set()
        self.negative = set()
        filep = open(positives, "r")
        filen = open(negatives, "r")

        for line in filep:
            if not line.startswith(';'):
                 self.positive.add(line.strip())
        self.positive.remove('')    

        for line in filen:
            if not line.startswith(';'):
                self.negative.add(line.strip())
        self.negative.remove('')
               
                

        filep.close()
        filen.close()

    def analyze(self, text, n):
        tweetz = helpers.get_user_timeline(text, n)
        if(tweetz == None):
            sys.exit("No tweets for {}".format(text))
        tokenizer = nltk.tokenize.TweetTokenizer()
        value = []
        Line = []
        i = 0
        pos = 0
        neg = 0
        nut = 0
        for line in tweetz:
            valueL = 0
            Line.append(line)
            tokens = tokenizer.tokenize(line)

            for word in tokens:
                if word.lower() in self.positive:
                    valueL = valueL + 1

                elif word.lower() in self.negative:
                    valueL = valueL - 1

                else:
                    valueL = valueL

            i = i + 1
            value.append(valueL)
            if valueL > 0:
                pos = pos + 1
            elif valueL < 0:
                neg = neg + 1
            else:
                nut = nut + 1

        return Line, value, pos, neg, nut
        
    def analyze2(self, word):
        valueL = 0
        if word.lower() in self.positive:
            valueL = valueL + 1
        elif word.lower() in self.negative:
            valueL = valueL - 1
        else:
            valueL = valueL
        return valueL
