import pygame
import sys
from settings import *
from tile import Tile
from player import Player
from debug import debug
from support import *
from random import choice, randint
from weapon import Weapon
from ui import UI
from enemy import Enemy
from particles import AnimationPlayer
from magic import MagicPlayer
from upgrade import Upgrade
from bag import Bag
from trap import Trap
from thing import Thing


class Level:
    def __init__(self,mode=1):

        # get the display surface
        self.display_surface = pygame.display.get_surface()
        self.game_menu = False

        # mode
        self.mode = int(1)
        # sprite group setup
        self.visible_sprites = YSortCameraGroup()
        self.obstacle_sprites = pygame.sprite.Group()
        self.trap_sprites = pygame.sprite.Group()

        # thing group
        self.pick_sprites = pygame.sprite.Group()
        # self.key = pygame.key.get_pressed()
        self.pickable_sprites = pygame.sprite.Group()
        # attack sprites
        self.current_attack = None
        self.attack_sprites = pygame.sprite.Group()
        self.attackable_sprites = pygame.sprite.Group()
        # state
        self.game_active = True
        # sprite setup
        self.create_map(self.game_active)
        self.map_test(False)
        # user interface
        self.ui = UI()
        self.upgrade = Upgrade(self.player)

        # particles
        self.animation_player = AnimationPlayer()
        self.magic_player = MagicPlayer(self.animation_player)

        # bag
        self.game_bag = False
        self.bag = Bag(self.player)

    def modify_mode(self,mode):
        self.mode = int(mode)
        print(self.mode)

    def mode_map(self):
        layouts = {
            'boundary': import_csv_layout('../graphics/tile/bacground_bounder.csv'),
            # # 'grass': import_csv_layout('../map/map_Grass.csv'),
            # 'object': import_csv_layout('../map/map_Objects.csv'),
            # 'object': import_csv_layout('../graphics/tile/bacground_second_floor.csv'),
            'entities': import_csv_layout('../map/map_Entities.csv'),
            'monster': import_csv_layout('../graphics/tile/bacground_monster.csv'),
            'monster1': import_csv_layout('../graphics/tile/bacground_monster2.csv'),
            'monster2': import_csv_layout('../graphics/tile/bacground_monster3.csv'),
            'test': import_csv_layout('../graphics/tile/bacground_object.csv'),
            'food': import_csv_layout('../graphics/tile/bacground_food.csv'),
            'trap': import_csv_layout('../graphics/tile/bacground_trap.csv')

        }
        for style, layout in layouts.items():
            for row_index, row in enumerate(layout):
                for col_index, col in enumerate(row):
                    if col != '-1':
                        x = col_index * TILESIZE
                        y = row_index * TILESIZE
                        if style == 'monster1' and self.mode > 1:
                            if col == '44':
                                monster_name = 'bamboo'
                            elif col == '33':
                                monster_name = 'spirit'
                            elif col == '98':
                                monster_name = 'raccoon'
                            else:
                                monster_name = 'squid'
                            Enemy(
                                monster_name,
                                (x, y),
                                [self.visible_sprites, self.attackable_sprites],
                                self.obstacle_sprites,
                                self.damage_player,
                                self.trigger_death_particles,
                                self.add_exp, self.modify_state)
                        if style == 'monster2' and self.mode > 2:
                            if col == '44':
                                monster_name = 'bamboo'
                            elif col == '33':
                                monster_name = 'spirit'
                            elif col == '98':
                                monster_name = 'raccoon'
                            else:
                                monster_name = 'squid'
                            Enemy(
                                monster_name,
                                (x, y),
                                [self.visible_sprites, self.attackable_sprites],
                                self.obstacle_sprites,
                                self.damage_player,
                                self.trigger_death_particles,
                                self.add_exp, self.modify_state)

    def map_test(self,state):
        if state:
            self.obstacle_sprites = pygame.sprite.Group()
            self.visible_sprites.change_floor()
            layouts = {
                'boundary': import_csv_layout('../graphics/boss/boss._boundary.csv'),
                'entities': import_csv_layout('../graphics/boss/boss._Tile Layer 2.csv'),
                'people': import_csv_layout('../graphics/boss/boss._Tile Layer 3.csv')


            }
            graphics = {
                # 'grass': import_folder('../graphics/Grass'),
                # 'objects': import_folder('../graphics/objects'),
                'objects': import_folder('../graphics/objectt')
            }
            for style, layout in layouts.items():
                for row_index, row in enumerate(layout):
                    for col_index, col in enumerate(row):
                        if col != '-1':
                            x = col_index * TILESIZE
                            y = row_index * TILESIZE
                            if style == 'boundary':
                                Tile((x, y), [self.obstacle_sprites], 'invisible')
                            if style == 'people':
                                if col == '87':
                                    monster_name = 'raccoon'
                                    Enemy(
                                        monster_name,
                                        (x, y),
                                        [self.visible_sprites, self.attackable_sprites],
                                        self.obstacle_sprites,
                                        self.damage_player,
                                        self.trigger_death_particles,
                                        self.add_exp, self.modify_state)
                                else:
                                    tmp = Player(
                                        (x, y),
                                        [self.visible_sprites, self.pick_sprites],
                                        self.obstacle_sprites,
                                        self.create_attack,
                                        self.destroy_attack,
                                        self.create_magic,
                                        self.map_test
                                    )
                                    tmp.player_bag = self.player.player_bag
                                    tmp.exp = self.player.exp
                                    tmp.health = self.player.health
                                    tmp.speed = self.player.speed
                                    self.player.kill()
                                    self.player = tmp










    def create_map(self,state):
        layouts = {
            'boundary': import_csv_layout('../graphics/tile/bacground_bounder.csv'),
            # # 'grass': import_csv_layout('../map/map_Grass.csv'),
            # 'object': import_csv_layout('../map/map_Objects.csv'),
            # 'object': import_csv_layout('../graphics/tile/bacground_second_floor.csv'),
            'entities': import_csv_layout('../map/map_Entities.csv'),
            'monster': import_csv_layout('../graphics/tile/bacground_monster.csv'),
            'monster1': import_csv_layout('../graphics/tile/bacground_monster2.csv'),
            'monster2': import_csv_layout('../graphics/tile/bacground_monster3.csv'),
            'test': import_csv_layout('../graphics/tile/bacground_object.csv'),
            'food': import_csv_layout('../graphics/tile/bacground_food.csv'),
            'trap': import_csv_layout('../graphics/tile/bacground_trap.csv')
            # 'bg': import_csv_layout('../graphics/tile/bacground_bg.csv'),
            # 'first': import_csv_layout('../graphics/tile/bacground_first_floor.csv'),
            # 'second': import_csv_layout('../graphics/tile/bacground_second_floor.csv')
            # "trap": import_csv_layout('')

        }
        graphics = {
            # 'grass': import_folder('../graphics/Grass'),
            # 'objects': import_folder('../graphics/objects'),
            'objects': import_folder('../graphics/objectt')
        }

        # test trap
        # trap_name = 'throny'
        # Trap(trap_name,
        #      (900, 400),
        #      [self.visible_sprites, self.attackable_sprites],
        #      self.trap_damage_player)
        # trap_name = 'spy_net'
        # Trap(trap_name,
        #      (840, 400),
        #      [self.visible_sprites, self.attackable_sprites],
        #      self.trap_damage_player)

        # test thing
        # thing_name = 'gold'
        # Thing(thing_name,
        #       (1400, 1400),
        #       [self.visible_sprites, self.pickable_sprites])

        for style, layout in layouts.items():
            for row_index, row in enumerate(layout):
                for col_index, col in enumerate(row):
                    if col != '-1':
                        x = col_index * TILESIZE
                        y = row_index * TILESIZE
                        if style == 'boundary':
                            Tile((x, y), [self.obstacle_sprites], 'invisible')
                        if style == 'grass':
                            random_grass_image = choice(graphics['grass'])
                            Tile(
                                (x, y),
                                [self.visible_sprites, self.obstacle_sprites, self.attackable_sprites],
                                'grass',
                                random_grass_image)
                        if style == 'food':
                            if col == '11':
                                Thing('gold',
                                      (x,y),
                                      [self.visible_sprites, self.pickable_sprites])
                            elif col == '22':
                                Thing('silver',
                                      (x,y),
                                      [self.visible_sprites, self.pickable_sprites])

                        if style == 'trap':
                            if col == '77':
                                Trap('spy_net',
                                     (x,y),
                                     [self.visible_sprites, self.attackable_sprites],
                                     self.trap_damage_player)

                            elif col == '87':
                                Trap('throny',
                                     (x,y),
                                     [self.visible_sprites, self.attackable_sprites],
                                     self.trap_damage_player)




                        if style == 'object':
                            surf = graphics['objects'][int(col)]
                            Tile((x, y), [self.visible_sprites, self.obstacle_sprites], 'object', surf)

                        if style == 'entities':
                            if col == '394':
                                self.player = Player(
                                    (x, y),
                                    [self.visible_sprites, self.pick_sprites],
                                    self.obstacle_sprites,
                                    self.create_attack,
                                    self.destroy_attack,
                                    self.create_magic,
                                    self.map_test
                                )

                            # if style == 'trap':
                            #     if col == '':
                            #         trap_name = ''
                            #     elif col == '':
                            #         trap_name = ''
                            #     else:
                            #         trap_name = ''
                            #     Trap(trap_name,
                            #          (x, y),
                            #          [self.visible_sprites, self.attackable_sprites],
                            #          self.trap_damage_player)

                        if style == 'monster':
                            if col == '44':
                                monster_name = 'bamboo'
                            elif col == '33':
                                monster_name = 'spirit'
                            elif col == '98':
                                monster_name = 'raccoon'
                            else:
                                monster_name = 'squid'
                            Enemy(
                                monster_name,
                                (x, y),
                                [self.visible_sprites, self.attackable_sprites],
                                self.obstacle_sprites,
                                self.damage_player,
                                self.trigger_death_particles,
                                self.add_exp,self.modify_state)
                        if style == 'monster1' and self.mode>1:
                            if col == '44':
                                monster_name = 'bamboo'
                            elif col == '33':
                                monster_name = 'spirit'
                            elif col == '98':
                                monster_name = 'raccoon'
                            else:
                                monster_name = 'squid'
                            Enemy(
                                monster_name,
                                (x, y),
                                [self.visible_sprites, self.attackable_sprites],
                                self.obstacle_sprites,
                                self.damage_player,
                                self.trigger_death_particles,
                                self.add_exp,self.modify_state)
                        if style == 'monster2' and self.mode > 2:
                            if col == '44':
                                monster_name = 'bamboo'
                            elif col == '33':
                                monster_name = 'spirit'
                            elif col == '98':
                                monster_name = 'raccoon'
                            else:
                                monster_name = 'squid'
                            Enemy(
                                monster_name,
                                (x, y),
                                [self.visible_sprites, self.attackable_sprites],
                                self.obstacle_sprites,
                                self.damage_player,
                                self.trigger_death_particles,
                                self.add_exp,self.modify_state)

    def pick_thing(self):
        if self.pick_sprites:
            for pick_sprite in self.pick_sprites:
                collision_sprites = pygame.sprite.spritecollide(pick_sprite, self.pickable_sprites, False)
                if collision_sprites:
                    for target_sprite in collision_sprites:
                        if target_sprite.sprite_type == 'thing':
                            name = target_sprite.thing_name
                            print(name)
                            print(self.player.player_bag['thing'][name])
                            if name == 'bullet':
                                self.player.player_bag['thing'][name] = self.player.player_bag['thing'][name] + 100
                            else:
                                self.player.player_bag['thing'][name] = self.player.player_bag['thing'][name] + 1
                            print(self.player.player_bag['thing'][name])
                            target_sprite.damage()

    # def use_thing(self):

    def create_attack(self):

        self.current_attack = Weapon(self.player, [self.visible_sprites, self.attack_sprites], self.shoot_bullet)

    def create_magic(self, style, strength, cost):
        if style == 'heal':
            self.magic_player.heal(self.player, strength, cost, [self.visible_sprites])

        if style == 'flame':
            self.magic_player.flame(self.player, cost, [self.visible_sprites, self.attack_sprites])

    def destroy_attack(self):
        if self.current_attack:
            print("666")
            self.current_attack.kill()
        self.current_attack = None

    def player_attack_logic(self):
        if self.attack_sprites:
            for attack_sprite in self.attack_sprites:
                collision_sprites = pygame.sprite.spritecollide(attack_sprite, self.attackable_sprites, False)
                if collision_sprites:
                    for target_sprite in collision_sprites:
                        if target_sprite.sprite_type == 'grass':
                            pos = target_sprite.rect.center
                            offset = pygame.math.Vector2(0, 75)
                            for leaf in range(randint(3, 6)):
                                self.animation_player.create_grass_particles(pos - offset, [self.visible_sprites])
                            target_sprite.kill()
                        elif target_sprite.sprite_type == 'trap':
                            pass
                        else:
                            target_sprite.get_damage(self.player, attack_sprite.sprite_type)

    def damage_player(self, amount, attack_type):
        if self.player.vulnerable:
            self.player.health -= amount
            if self.player.health <= 0:
                self.game_active = False
            self.player.vulnerable = False
            self.player.hurt_time = pygame.time.get_ticks()
            self.animation_player.create_particles(attack_type, self.player.rect.center, [self.visible_sprites])

    def trap_damage_player(self, amount, trap_name):
        if self.player.vulnerable:
            if trap_name == 'throny':
                self.player.health -= amount
                if self.player.health <= 0:
                    self.game_active = False
                self.player.vulnerable = False
                self.player.hurt_time = pygame.time.get_ticks()
            elif trap_name == 'spy_net' and self.player.vulnerable_speed:
                print(amount)
                self.player.vulnerable_speed = False
                print(self.player.speed)
                self.player.speed -= amount
                print(self.player.speed)
                self.player.hurt_speed_time = pygame.time.get_ticks()
            else:
                self.player.vulnerable = False
                self.player.hurt_time = pygame.time.get_ticks()

    def trigger_death_particles(self, pos, particle_type):

        self.animation_player.create_particles(particle_type, pos, self.visible_sprites)

    def add_exp(self, amount):

        self.player.exp += amount

    def toggle_menu(self):

        self.game_menu = not self.game_menu

    def modify_state(self):
        self.game_active = False;

    def toggle_bag(self):

        self.game_bag = not self.game_bag

    def shoot_bullet(self, player,centerx,centery):
        player.player_bag['thing']['bullet'] -= 1
        if player.status.split('_')[0] == 'right':
            direction = pygame.math.Vector2(1, 0)
        elif player.status.split('_')[0] == 'left':
            direction = pygame.math.Vector2(-1, 0)
        elif player.status.split('_')[0] == 'up':
            direction = pygame.math.Vector2(0, -1)
        else:
            direction = pygame.math.Vector2(0, 1)

        for i in range(1, 6):
            if direction.x > 0:  # horizontal
                offset_x = (direction.x * i) * TILESIZE
                # offset_x = (direction.x * 1) * TILESIZE
                x = player.rect.centerx + offset_x + i+30
                y = player.rect.centery+5
                self.animation_player.create_particles_bullet('bullet_' + player.status.split('_')[0], (x, y),
                                                              [self.visible_sprites, self.attack_sprites])
            elif direction.x < 0:  # horizontal
                offset_x = (direction.x * i) * TILESIZE
                # offset_x = (direction.x * 1) * TILESIZE
                x = player.rect.centerx + offset_x + i -30
                y = player.rect.centery+5
                self.animation_player.create_particles_bullet('bullet_' + player.status.split('_')[0], (x, y),
                                                              [self.visible_sprites, self.attack_sprites])
            elif direction.y > 0:  # horizontal
                offset_y = (direction.y * i) * TILESIZE
                # offset_y = (direction.y * 1) * TILESIZE
                x = player.rect.centerx
                y = player.rect.centery + offset_y + i +30
                self.animation_player.create_particles_bullet('bullet_' + player.status.split('_')[0], (x, y),
                                                              [self.visible_sprites, self.attack_sprites])
            else:  # vertical
                offset_y = (direction.y * i) * TILESIZE
                # offset_y = (direction.y * 1) * TILESIZE
                x = player.rect.centerx
                y = player.rect.centery + offset_y + i -35
                self.animation_player.create_particles_bullet('bullet_' + player.status.split('_')[0], (x, y),
                                                              [self.visible_sprites, self.attack_sprites])

    def run(self):
        #  画画面
        # self.visible_sprites.draw(self.display_surface)
        self.visible_sprites.custom_draw(self.player)
        self.ui.display(self.player)

        if self.game_bag and not self.game_menu:
            self.bag.display(self.player)
        elif self.game_menu and not self.game_bag:
            self.upgrade.display()
        elif not self.game_bag and not self.game_menu:
            self.visible_sprites.update()
            self.visible_sprites.enemy_update(self.player)
            self.visible_sprites.trap_update(self.player)
            self.player_attack_logic()
            # for event in pygame.event.get():
            #     if event.type == pygame.KEYDOWN:
            #         print(4)

            test = pygame.key.get_pressed()
            if test[pygame.K_p]:
                self.pick_thing()

    def modify_state(self):
        self.game_active = False


class YSortCameraGroup(pygame.sprite.Group):
    def __init__(self):

        # general setup
        super().__init__()
        self.display_surface = pygame.display.get_surface()
        self.half_width = self.display_surface.get_size()[0] // 2
        self.half_height = self.display_surface.get_size()[1] // 2
        self.offset = pygame.math.Vector2()

        # creating the floor
        self.floor_surf = pygame.image.load('../graphics/tile/map.png').convert()

        self.floor_rect = self.floor_surf.get_rect(topleft=(0, 0))
    def change_floor(self):
        self.floor_surf = pygame.image.load('../graphics/boss/boss.png').convert()
        self.floor_rect = self.floor_surf.get_rect(topleft=(0, 0))
    def custom_draw(self, player):

        # getting the offset
        self.offset.x = player.rect.centerx - self.half_width
        self.offset.y = player.rect.centery - self.half_height

        # drawing the floor
        floor_offset_pos = self.floor_rect.topleft - self.offset
        self.display_surface.blit(self.floor_surf, floor_offset_pos)

        # for sprite in self.sprites():
        for sprite in sorted(self.sprites(), key=lambda sprite: sprite.rect.centery):
            offset_pos = sprite.rect.topleft - self.offset
            self.display_surface.blit(sprite.image, offset_pos)

    def enemy_update(self, player):
        enemy_sprites = [sprite for sprite in self.sprites() if
                         hasattr(sprite, 'sprite_type') and sprite.sprite_type == 'enemy']
        for enemy in enemy_sprites:
            enemy.enemy_update(player)

    def trap_update(self, player):
        trap_sprites = [sprite for sprite in self.sprites() if
                        hasattr(sprite, 'sprite_type') and sprite.sprite_type == 'trap']
        for trap in trap_sprites:
            trap.trap_update(player)
