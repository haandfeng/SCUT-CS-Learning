import pygame
from settings import *
import operator
from support import import_folder

'''待完成任务： 1.美化背景 2.字体大小 3.背包方框大小位置 4.图片递进 和位置 '''


class Bag:
    def __init__(self, player):
        # itemlist
        self.thingitemlist = []
        self.weaponitemlist = []
        # general setting
        self.display_surface = pygame.display.get_surface()
        self.player = player
        self.font = pygame.font.Font(UI_FONT, UI_FONT_SIZE)
        self.bag_name = 'thing'

        # length
        self.length = len(player.player_bag)

        # bg creation
        self.left = self.display_surface.get_size()[0] * 0.1
        self.top = self.display_surface.get_size()[1] * 0.1
        self.height = self.display_surface.get_size()[1] * 0.8
        self.width = self.display_surface.get_size()[0] * 0.8

        self.bg_height = self.display_surface.get_size()[1] * 0.8
        self.bg_width = self.display_surface.get_size()[0] * 0.5
        self.bg_rect = pygame.Rect(self.left, self.top, self.width, self.height)

        # selection and cooldown
        self.selection_index_x = 1
        self.selection_index_y = 1
        self.max_x = 13
        self.max_y = 7
        self.selection_time = None
        self.using_time = None
        self.can_move = True
        self.can_use = True

        # font
        self.title_color = TEXT_COLOR_SELECTED
        self.title = self.font.render("Bag", False, self.title_color)
        self.title_rect = self.title.get_rect(midtop=self.bg_rect.midtop + pygame.math.Vector2(0, 20))

        self.thing = self.font.render("Thing", False, self.title_color)
        self.thing_rect = self.thing.get_rect(topleft=self.bg_rect.topleft - pygame.math.Vector2(0, 20))
        self.index_thing_x = 1
        self.index_thing_y = 0

        self.weapon = self.font.render("Weapon", False, self.title_color)
        self.weapon_rect = self.weapon.get_rect(topleft=self.bg_rect.topleft - pygame.math.Vector2(-200, 20))
        self.index_weapon_x = 2
        self.index_weapon_y = 0

        #     use things
        self.thingx = 1
        self.thingy = 1

    def input(self):
        keys = pygame.key.get_pressed()

        if self.can_move:
            if keys[pygame.K_RIGHT] and ((self.selection_index_y != 0 and self.selection_index_x < self.max_x) or (
                    self.selection_index_y == 0 and self.selection_index_x <= 1)):
                self.selection_index_x += 1
                self.can_move = False
                self.selection_time = pygame.time.get_ticks()
            elif keys[pygame.K_LEFT] and self.selection_index_x >= 2:
                self.selection_index_x -= 1
                self.can_move = False
                self.selection_time = pygame.time.get_ticks()
            elif keys[pygame.K_DOWN] and self.selection_index_y < self.max_y:
                self.selection_index_y += 1
                self.can_move = False
                self.selection_time = pygame.time.get_ticks()
            elif keys[pygame.K_UP] and (
                    self.selection_index_y == 1 and self.selection_index_x <= 2 or self.selection_index_y > 1):
                self.selection_index_y -= 1
                self.can_move = False
                self.selection_time = pygame.time.get_ticks()
            elif keys[pygame.K_s]:
                self.can_move = False
                print(self.player.player_bag['thing'])
                self.player.player_bag['thing'] = dict(sorted(self.player.player_bag['thing'].items(),  key=lambda d: d[1], reverse=True))
                self.selection_time = pygame.time.get_ticks()
                self.thingitemlist = []
                self.weaponitemlist = []
                print(self.player.player_bag['thing'])
        if self.can_use:
            if keys[pygame.K_LCTRL]:
                self.can_use = False
                self.using_time = pygame.time.get_ticks()
                if self.bag_name == 'thing':
                    self.player.usething2(self.thingitemlist[self.selection_index_x - 1].getname())
                    print(self.thingitemlist[self.selection_index_x - 1].getname())
                elif self.bag_name == 'weapon':
                    self.player.weapon = self.weaponitemlist[self.selection_index_x - 1].getname()
                    self.player.weapon_index = 0
                    while list(weapon_data.keys())[self.player.weapon_index] != self.weaponitemlist[
                        self.selection_index_x - 1].getname():
                        self.player.weapon_index += 1
                    print(self.weaponitemlist[self.selection_index_x - 1].getname())
                # self.item_list[self.selection_index].trigger(self.player)

    def selection_cooldown(self):
        if not self.can_move:
            current_time = pygame.time.get_ticks()
            if current_time - self.selection_time >= 200:
                self.can_move = True
        if not self.can_use:
            current_time = pygame.time.get_ticks()
            if current_time - self.using_time >= 200:
                self.can_use = True

    def create_item(self, player):
        self.thingitemlist = []
        self.weaponitemlist = []
        index_X = 0
        for x in range(128, self.display_surface.get_size()[0] - int(self.left), 64 + 16):
            index_X += 1
            index_Y = 0
            for y in range(72 + 16, self.display_surface.get_size()[1] - int(self.top), 64 + 16):
                index_Y += 1
                item_grid = Item(x, y, "grid", index_X, index_Y)
                item_grid.draw_grid(self.display_surface, self.selection_index_x, self.selection_index_y, player)
        pos = [128 + 32, 72 + 16 + 32]
        for name in list(player.player_bag[self.bag_name].keys()):
            if player.player_bag[self.bag_name][name] > 0:
                # print(name)
                item = Item(pos[0], pos[1], name, sindex=self.thingx)
                # 新加
                if self.bag_name == 'thing':
                    self.thingitemlist.append(item)
                elif self.bag_name == 'weapon':
                    self.weaponitemlist.append(item)
                item.display(self.display_surface, self.bag_name, player, )
                # new show nmuber
                if player.player_bag['thing'][player.thing_list[player.thing_index]] > 0 and self.bag_name == 'thing':
                    font2 = pygame.font.Font(UI_FONT, 12)
                    thing_number = font2.render(str(player.player_bag[self.bag_name][name]),
                                                False,
                                                WATER_COLOR)
                    thing_number_rect = thing_number.get_rect(
                        center=(pos[0] + 32, pos[1] + 32) - pygame.math.Vector2(30, 12))
                    self.display_surface.blit(thing_number, thing_number_rect)
                '有问题要修改'
                pos[0] = pos[0] + 80
                self.thingx += 1

    def display(self, player):
        pygame.draw.rect(self.display_surface, WATER_COLOR, self.bg_rect)

        # print(self.selection_index_x, self.selection_index_y)

        if self.selection_index_y == self.index_thing_y and self.selection_index_x == self.index_thing_x:
            self.bag_name = 'thing'
            self.thing.set_colorkey(UI_BG_COLOR)
        else:
            self.thing.set_colorkey(UPGRADE_BG_COLOR_SELECTED)

        if self.selection_index_y == self.index_weapon_y and self.selection_index_x == self.index_weapon_x:
            self.bag_name = 'weapon'
            self.weapon.set_colorkey(UI_BG_COLOR)
        else:
            self.weapon.set_colorkey(UPGRADE_BG_COLOR_SELECTED)

        self.display_surface.blit(self.title, self.title_rect)
        self.display_surface.blit(self.thing, self.thing_rect)
        self.display_surface.blit(self.weapon, self.weapon_rect)
        self.input()
        self.selection_cooldown()
        if player.player_bag['thing']['gold'] > 0:
            pass
            # print(1)
        self.create_item(player)


# 背包图片和格子
class Item():
    def __init__(self, x, y, typename='', index_x=-2, index_y=-2, sindex=1):
        self.name = typename
        self.x = x
        self.y = y
        self.index_x = index_x
        self.index_y = index_y

    def display(self, surface, bag_name, player):
        if bag_name == 'thing':
            self.image = pygame.image.load(item_data[self.name]['graphic']).convert_alpha()
        elif bag_name == 'weapon':
            self.image = pygame.image.load(weapon_data[self.name]['graphic']).convert_alpha()

        # self.rect = self.image.get_rect(topleft=(self.x, self.y))
        if self.name == '':
            self.rect = self.image.get_rect(topleft=(self.x, self.y))
        else:
            self.rect = self.image.get_rect(center=(self.x, self.y))
        surface.blit(self.image, self.rect)

    def cenx(self):
        return self.rect.centerx

    def ceny(self):
        return self.rect.centery

    def draw_grid(self, surface, select_x, select_y, player):
        grid_width = 64
        grid_height = 64
        if select_x == self.index_x and select_y == self.index_y:
            # print(self.index_y,self.index_x)
            grid_rect = pygame.Rect(self.x, self.y, grid_width, grid_height)
            pygame.draw.rect(surface, UI_BG_COLOR, grid_rect)
            pygame.draw.rect(surface, UI_BORDER_COLOR, grid_rect, 4)

        else:
            grid_rect = pygame.Rect(self.x, self.y, grid_width, grid_height)
            pygame.draw.rect(surface, UPGRADE_BG_COLOR_SELECTED, grid_rect)
            pygame.draw.rect(surface, UI_BORDER_COLOR, grid_rect, 4)

    def getname(self):
        return self.name
