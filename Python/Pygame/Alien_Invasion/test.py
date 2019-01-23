import pygame,sys

WHITE = (255, 255, 255)
GREEN = ( 0, 255, 0)
BLUE = ( 0, 0, 128)

def run():
    pygame.init()
    font = pygame.font.Font('C:\Windows\Fonts\PAPYRUS.ttf', 48)
    screen = pygame.display.set_mode((500,500))
    pygame.display.set_caption("Hello,World")
    while True:
        for event in pygame.event.get():
            if event.type == pygame.KEYDOWN:
                ff = font.render(str(event.key),True,GREEN,BLUE)
                position = ff.get_rect()
                position.center = (200,150)
                screen.fill(WHITE)
                screen.blit(ff,position)
                pygame.display.flip()

run()