import sys
import pygame
from pygame.sprite import Group
import game_functions as gf
from settings import Settings
from ship import Ship
from alien import Alien
from game_stats import GameStats
from scoreboard import Scoreboard
from button import Button
#import settings

def run_game():
    pygame.init()
    pygame.mixer.music.load("C:/Users/GowJK/OneDrive/IT/Code/Python/Pygame/Alien_Invasion/sound/bgm.ogg")
    pygame.mixer.music.play(-1)
 #  ai_settings = settings.Settings()
    ai_settings = Settings()
    screen = pygame.display.set_mode((ai_settings.screen_width,ai_settings.screen_height))
    ship = Ship(ai_settings,screen)
    bullets = Group()
    aliens = Group()
    gf.create_fleet(ai_settings,screen,ship,aliens)
    stats = GameStats(ai_settings)
    play_button = Button(ai_settings,screen,"Play")
    pygame.display.set_caption("Alien Invasion")
    scoreboard = Scoreboard(ai_settings,screen,stats)
    while True:
        gf.check_events(ai_settings,screen,stats,scoreboard,play_button,ship,aliens,bullets)
        if stats.game_active == True:
            ship.update()
            gf.update_bullets(ai_settings,screen,stats,scoreboard,ship,aliens,bullets)
            gf.update_aliens(ai_settings,stats,scoreboard,screen,ship,aliens,bullets)

        gf.update_screen(ai_settings,screen,stats,scoreboard,ship,aliens,bullets,play_button)
        
run_game()