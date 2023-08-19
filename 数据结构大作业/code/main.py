import pygame, sys
from settings import *
import time
import support
from debug import *
from level import Level
player_stand = pygame.image.load('../graphics/11.jpg')
player_stand = pygame.transform.rotozoom(player_stand, 0, 0.5)
player_stand_rect = player_stand.get_rect()
class Game:
    def __init__(self):

        # general setup
        pygame.init()
        self.screen = pygame.display.set_mode((WIDTH, HEIGTH))
        # 改名
        pygame.display.set_caption('Tomb Raider')
        self.clock = pygame.time.Clock()
        self.game_active = False
        self.count = 0
        self.level = []
        for i in range(INI):
            self.level.append(Level())

        # sound
        main_sound = pygame.mixer.Sound('../audio/main.ogg')
        main_sound.set_volume(0.5)
        main_sound.play(loops=-1)

    def run(self):
        while True:
            # 定义字幕持续显示时间（秒）
            subtitle_duration = 2
            # 定义背景和字幕颜色
            background_color = (0, 0, 0)
            text_color = (255, 255, 255)
            # 记录字幕开始显示的时间
            subtitle_start_time = 0
            show_prompt = False



            for event in pygame.event.get():
                if event.type == pygame.QUIT:
                    pygame.quit()
                    sys.exit()
                if self.game_active:
                    if event.type == pygame.KEYDOWN:
                        if event.key == pygame.K_m and not self.level[self.count].game_bag:
                            self.level[self.count].toggle_menu()
                        if event.key == pygame.K_b and not self.level[self.count].game_menu:
                            self.level[self.count].toggle_bag()
                        # if event.key == pygame.K_l and self.level[self.count].player.hitbox.x >= 1800 \
                        #     and self.level[self.count].player.hitbox.x <= 1900 \
                        #     and self.level[self.count].player.hitbox.y >= 2100 \
                        #     and self.level[self.count].player.hitbox.y <= 2250:
                        #     print("跳转到BOSS战")
                    if event.type == pygame.KEYUP and event.key == pygame.K_f:
                        self.level[self.count].player.can_show_caption = True


                if not self.game_active:
                    if event.type == pygame.KEYDOWN and event.key == pygame.K_1:
                        self.level[self.count].modify_mode(1)

                        self.game_active = True

                    if event.type == pygame.KEYDOWN and event.key == pygame.K_2:
                        self.level[self.count].modify_mode(2)
                        self.level[self.count].mode_map()
                        self.game_active = True

                    if event.type == pygame.KEYDOWN and event.key == pygame.K_3:
                        self.level[self.count].modify_mode(3)
                        self.level[self.count].mode_map()
                        self.game_active = True



            if self.game_active:
                self.screen.fill(WATER_COLOR)
                self.level[self.count].run()

                if not self.level[self.count].game_active:
                    self.game_active = False
                    support.kill_number = 0
                    self.count += 1

            else:
                self.screen.blit(player_stand,player_stand_rect)
                font = pygame.font.SysFont("freesansbold.ttf", 50)  # 30:font size
                text1 = font.render("PRESS 1 SIMPLE MODE",True, (220,220,220))
                text2 = font.render("PRESS 2 MEDIUM MODE",True, (220,220,220))
                text3 = font.render("PRESS 3 NIGHTMARE",True, (220,220,220)) # (0,0,0) color of font
                self.screen.blit(text1,(HEIGTH-290,WIDTH/2-310))
                self.screen.blit(text2,(HEIGTH-290,WIDTH/2-190))
                self.screen.blit(text3,(HEIGTH-290,WIDTH/2-70))# (10,10) rect left top

            pygame.display.update()
            self.clock.tick(FPS)


if __name__ == '__main__':
    game = Game()
    game.run()
