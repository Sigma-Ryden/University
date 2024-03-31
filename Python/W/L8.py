import getpass

def str_to_int_arr(string):
    out = []
    for symbol in string:
        out.append(ord(symbol))
        
    return out
        
def int_arr_to_str(integer_array):
    out = ""
    for number in integer_array:
        out += chr(number)

    return out
    
    
class HangMan:
    # view_preset - contains visual data for real game progress
    def __init__(self, view_preset=[], pattern='*'):
        self.__view_preset = view_preset if len(view_preset) > 1 else self.__default_view_preset()
        self.reset()
        self.pattern(pattern)
        
    def __default_view_preset(self):
        return [9, 8, 7, 6, 5, 4, 3, 2, 1, 0]

    # word - secret word (can be inited by play func)
    # guess - already known secret word symbols
    # state - game state [-1 if lose] or [0 if in progress] or [1 if won]
    # done - game state [False if game in progress] or [True if game is lose or won]
    def reset(self):
        self.__lose_count = 0
        self.__win_count = 0
        self.__word = []
        self.__guess = []
        self.__state = 0
        self.__done = False
    
    def pattern(self, pattern):
        self.__pattern = ord(pattern)
        
    # set of new secret word
    def play(self, word):
        if len(word) == 0:
            return self.__done_state()
        
        self.reset()
        
        self.__word = str_to_int_arr(word.lower())
        self.__guess = [self.__pattern] * len(word)
        
        return self.__in_progress_state()

    # will not recomended use in native game - only for check
    def word(self):
        return int_arr_to_str(self.__word)
        
    # return guess partialy word with pattern filler
    def guess(self):
        return int_arr_to_str(self.__guess)
        
    def __update_guess(self, symbol):
        for i in range(len(self.__guess)):
            if symbol == self.__word[i]:
                self.__guess[i] = symbol
        
    def is_ready(self):
        return self.__lose_count == 0 and self.__win_count == 0 and self.__word != "" and self.__guess == "" and self.__state == 0 and self.__done == False

    def state(self):
        return self.__state;

    # return [True if game was won or lose] or [False if game in progress]
    def is_done(self):
        return self.__state != 0 and self.__done == True


    def attempt_total(self):
        return len(self.__view_preset)

    def attempt_left(self):
        return self.attempt_total() - self.__lose_count

    def win_count(self):
        return self.__win_count


    def __lose_state(self):
        return -1

    def __in_progress_state(self):
        return 0

    def __win_state(self):
        return 1

    def __done_state(self):
        return 2


    def __update_lose_state(self):
        if self.__lose_count == self.attempt_total():
            return self.__done_state()
        else: 
            self.__lose_count += 1
            return self.__lose_state()

    def __update_win_state(self, symbol):
        if self.__win_count == len(self.__word):
            return self.__done_state()
        else:
            self.__update_guess(symbol)
            self.__win_count += self.__word.count(symbol)            
            return self.__win_state()


    def __update_game_state(self):
        if self.__lose_count == len(self.__view_preset):
            self.__state = -1
            self.__done = True
        
        elif self.__win_count == len(self.__word):
            self.__state = 1
            self.__done = True
        
        else:
            self.__state = 0
            self.__done = False


    # return [[-1 if word does not] or [0 if guess already] or [1 if guess does not] contain a symbol] or [2 if game is done]
    def step(self, symbol):
        symbol = ord(symbol.lower())
        # state_code only for current step - not for gloal game session
        state_code = self.__done_state()

        if self.is_done():
            return state_code

        if symbol in self.__word:
            if symbol in self.__guess:
                state_code = self.__in_progress_state()
            else: 
                self.__update_win_state(symbol)
                state_code = self.__win_state()
        else:
            self.__update_lose_state()
            state_code = self.__lose_state()

        self.__update_game_state()

        return state_code

    # return current view_preset item
    def view(self):
        return self.__view_preset[self.__lose_count]


def new_session():
    game = HangMan()
    
    word = getpass.getpass('Enter secret word: ')
    game.play(word)

    while not game.is_done():
        print('Current game state:', game.guess())
        print(game.view())
    
        symbol = str(input('Enter a symbol: '))
        result = game.step(symbol)

        if result == -1:
            print('Incorrect symbol! Left trying:', game.attempt_left())

        elif result == 0:
            print('Symbol is already has!')

        elif result == 1:
            print('Correct symbol!')
        
        print()

    print('You', 'lose' if game.state() == -1 else 'won', '!')
    print('Word:', game.word())
    
    
while True:
    new_session()