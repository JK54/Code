import os

class GameStats():
    def __init__(self,ai_settings):
        self.ai_settings = ai_settings
        self.reset_stats()
        self.game_active = False
        if os.stat("high_score.txt").st_size == 0:
            self.high_score = 0
        else:
            with open("high_score.txt",'r') as fs:
                high_score = fs.read()
                self.high_score = int(high_score)
    def reset_stats(self):
        self.ship_left = self.ai_settings.ship_limit
        self.score = 0
        self.level = 1