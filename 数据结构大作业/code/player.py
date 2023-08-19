import pygame
from debug import *
from settings import *
from support import import_folder
from entity import Entity
from particles import AnimationPlayer
import support


class Player(Entity):
    def __init__(self, pos, groups, obstacle_sprites, create_attack, destroy_attack, create_magic,new_map):
        super().__init__(groups)

        self.image = pygame.image.load('../graphics/test/player.png').convert_alpha()
        self.rect = self.image.get_rect(topleft=pos)
        self.hitbox = self.rect.inflate(-6, HITBOX_OFFSET['player'])
        self.sprite_type = 'player'
        # self.shoot_bullet = shoot_bullet
        # Bag
        self.is_new_map = False

        self.player_bag = {
            'thing': {'gold': 1,
                      'silver': 3,
                      'bullet': 100},
            'weapon': {'sword': 1,
                       'lance': 1,
                       'axe': 1,
                       'rapier': 1,
                       'sai': 1,
                       'gun': 1
                       }
        }

        # graphics setup
        self.import_player_assets()
        self.status = 'down'

        # movement
        self.attacking = False
        self.attack_cooldown = 400
        self.attack_time = None
        self.obstacle_sprites = obstacle_sprites
        # self.trap_sprites = trap_sprites
        # weapon
        self.create_attack = create_attack
        self.destroy_attack = destroy_attack
        self.weapon_index = 0
        self.weapon = list(weapon_data.keys())[self.weapon_index]
        self.can_switch_weapon = True
        self.weapon_switch_time = None
        self.switch_duration_cooldown = 200
        # caption
        self.can_show_caption = True


        #new_map
        self.new_map = new_map
        # magic
        self.create_magic = create_magic
        self.magic_index = 0
        self.magic = list(magic_data.keys())[self.magic_index]
        self.can_switch_magic = True
        self.magic_switch_time = None

        # stats
        self.stats = {'health': 150,  'attack': 10, 'speed': 5}
        self.max_stats = {'health': 300,  'attack': 20,  'speed': 10}
        self.upgrade_cost = {'health': 100,  'attack': 100,  'speed': 100}
        self.health = self.stats['health'] * 1
        # self.energy = self.stats['energy'] * 0.8
        self.exp = 5000
        self.speed = self.stats['speed']

        # damage timer
        self.vulnerable = True
        self.vulnerable_speed = True
        self.hurt_time = None
        self.hurt_speed_time = None
        self.invulnerability_duration = 500
        self.invulnerability_speed_duration = 2500

        # import a sound
        self.weapon_attack_sound = pygame.mixer.Sound('../audio/sword.wav')
        self.weapon_attack_sound.set_volume(0.4)

        # magic
        # self.create_magic = create_magic
        self.thing_index = 0
        self.thing_list = []

        #is_jump
        self.jump = False

        self.can_switch_thing = True
        self.using_thing = False
        self.thing_switch_time = None
        self.using_thing_cooldown = 400
        self.using_thing_time = None
        self.update_thing_list()
        self.thing = None
    def position(self):
        # debug((self.hitbox.x,self.hitbox.y))
        pass
    def update_thing_list(self):
        self.thing_list = []
        for key in self.player_bag['thing'].keys():
            if self.player_bag['thing'][key] > 0:
                self.thing_list.append(key)

    def update_thing(self):
        if self.thing_list:
            self.thing = self.thing_list[self.thing_index]
        else:
            self.thing = None

    def show_caption(self):
        if not self.is_new_map:
            x, y = self.hitbox.x, self.hitbox.y
            if x >= 1800 and x <= 1900 and y >= 2100 and y <= 2250:
                self.jump = True

                if self.can_show_caption:
                    caption("Press J, jump to the next LEVEL")
            else:
                self.jump = False

    def import_player_assets(self):
        character_path = '../graphics/player/'
        self.animations = {'up': [], 'down': [], 'left': [], 'right': [],
                           'right_idle': [], 'left_idle': [], 'up_idle': [], 'down_idle': [],
                           'right_attack': [], 'left_attack': [], 'up_attack': [], 'down_attack': []}

        for animation in self.animations.keys():
            full_path = character_path + animation
            self.animations[animation] = import_folder(full_path)

    def usething(self):
        self.using_thing = True
        self.using_thing_time = pygame.time.get_ticks()
        self.update_thing()
        a = len(self.thing_list)
        if self.thing and self.thing != 'bullet':
            if self.player_bag['thing'][self.thing] >= 1:
                self.player_bag['thing'][self.thing] = self.player_bag['thing'][self.thing] - 1

            if self.stats['health'] >= self.health + self.get_full_thing_recovery():
                self.health += self.get_full_thing_recovery()
            else:
                self.health = self.stats['health']
            self.update_thing_list()
        if a != len(self.thing_list):
            self.swap_thing()

    def usething2(self, name):
        self.using_thing = True
        self.using_thing_time = pygame.time.get_ticks()
        self.update_thing()
        self.thing = name
        if name and name != 'bullet':

            if self.player_bag['thing'][name] >= 1:
                self.player_bag['thing'][name] = self.player_bag['thing'][name] - 1

            if self.stats['health'] >= self.health + self.get_full_thing_recovery():
                print(1)
                self.health += self.get_full_thing_recovery()
                # print(self.health)
                print(self.player_bag['thing'])
            else:
                self.health = self.stats['health']
            self.update_thing_list()
        a = len(self.thing_list)

        if a != len(self.thing_list):
            self.swap_thing()

    def swap_thing(self):

        self.update_thing_list()
        if self.thing_index < len(self.thing_list) - 1:
            self.thing_index += 1
        else:
            self.thing_index = 0
        if self.thing_list:
            self.thing = self.thing_list[self.thing_index]
        else:
            self.thing = None

    def input(self):

        if not self.attacking and not self.using_thing:
            keys = pygame.key.get_pressed()

            # movement input
            if keys[pygame.K_UP]:
                self.direction.y = -1
                self.status = 'up'
            elif keys[pygame.K_DOWN]:
                self.direction.y = 1
                self.status = 'down'
            else:
                self.direction.y = 0

            if keys[pygame.K_RIGHT]:
                self.direction.x = 1
                self.status = 'right'
            elif keys[pygame.K_LEFT]:
                self.direction.x = -1
                self.status = 'left'
            else:
                self.direction.x = 0

            if keys[pygame.K_j]:
                if support.kill_number < 5:
                    self.can_show_caption = False
                    caption("Killed Monster should more than 5!")

                if not self.is_new_map and self.jump and support.kill_number >= 5:
                    self.can_show_caption = False
                    self.new_map(True)
                    self.is_new_map = True
            else:
                self.can_show_caption = True
            # if keys[pygame.K_l]:
            #     if self.hitbox.x >= 1800 and self.hitbox.x <= 1900\
            #         and self.hitbox.y >= 2100 and self.hitbox.y <= 2250:
            #             print("跳转")

            # attack input
            if keys[pygame.K_SPACE]:
                self.attacking = True
                self.attack_time = pygame.time.get_ticks()
                self.create_attack()
                self.weapon_attack_sound.play()



            # use thing
            if keys[pygame.K_LCTRL]:
                self.usething()
                # self.using_thing = True
                # self.using_thing_time = pygame.time.get_ticks()
                # self.update_thing()
                # a = len(self.thing_list)
                # if self.thing and self.thing != 'bullet':
                #     if self.player_bag['thing'][self.thing] >= 1:
                #         self.player_bag['thing'][self.thing] = self.player_bag['thing'][self.thing] - 1
                #
                #     if self.stats['health'] >= self.health + self.get_full_thing_recovery():
                #         self.health += self.get_full_thing_recovery()
                #     else:
                #         self.health = self.stats['health']
                #     self.update_thing_list()
                # if a != len(self.thing_list):
                #     self.swap_thing()
                # style = list(magic_data.keys())[self.magic_index]
                # strength = list(magic_data.values())[self.magic_index]['strength'] + self.stats['magic']
                # cost = list(magic_data.values())[self.magic_index]['cost']
                # self.create_magic(style, strength, cost)

            if keys[pygame.K_q] and self.can_switch_weapon:
                self.can_switch_weapon = False
                self.weapon_switch_time = pygame.time.get_ticks()

                if self.weapon_index < len(list(weapon_data.keys())) - 1:
                    self.weapon_index += 1
                else:
                    self.weapon_index = 0

                self.weapon = list(weapon_data.keys())[self.weapon_index]

            # if keys[pygame.K_e] and self.can_switch_magic:
            #     self.can_switch_magic = False
            #     self.magic_switch_time = pygame.time.get_ticks()
            #
            #     if self.magic_index < len(list(magic_data.keys())) - 1:
            #         self.magic_index += 1
            #     else:
            #         self.magic_index = 0
            #
            #     self.magic = list(magic_data.keys())[self.magic_index]

            if keys[pygame.K_e] and self.can_switch_thing:
                self.can_switch_thing = False
                self.thing_switch_time = pygame.time.get_ticks()
                self.swap_thing()
            # if keys[pygame.K_p] and self.can_pick_thing:
            #     self.can_pick_thing = False
            #     self.pick_time = pygame.time.get_ticks()
            #     self.pick_thing()


    def get_status(self):

        # idle status
        if self.direction.x == 0 and self.direction.y == 0:
            if not 'idle' in self.status and not 'attack' in self.status:
                self.status = self.status + '_idle'

        if self.attacking:
            self.direction.x = 0
            self.direction.y = 0
            if not 'attack' in self.status:
                if 'idle' in self.status:
                    self.status = self.status.replace('_idle', '_attack')
                else:
                    self.status = self.status + '_attack'
        else:
            if 'attack' in self.status:
                self.status = self.status.replace('_attack', '')

    def cooldowns(self):
        current_time = pygame.time.get_ticks()
        if self.attacking:
            if current_time - self.attack_time >= self.attack_cooldown + weapon_data[self.weapon]['cooldown']:
                self.attacking = False
                self.destroy_attack()
                print("cnm")

        if self.using_thing:
            if current_time - self.using_thing_time >= self.using_thing_cooldown:
                self.using_thing = False

        if not self.can_switch_weapon:
            if current_time - self.weapon_switch_time >= self.switch_duration_cooldown:
                self.can_switch_weapon = True

        # if not self.can_switch_magic:
        #     if current_time - self.magic_switch_time >= self.switch_duration_cooldown:
        #         self.can_switch_magic = True

        if not self.can_switch_thing:
            if current_time - self.thing_switch_time >= self.switch_duration_cooldown:
                self.can_switch_thing = True

        if not self.vulnerable:
            if current_time - self.hurt_time >= self.invulnerability_duration:
                self.vulnerable = True
        if not self.vulnerable:
            if current_time - self.hurt_time >= self.invulnerability_duration:
                self.vulnerable = True
        if not self.vulnerable_speed:
            if current_time - self.hurt_speed_time >= self.invulnerability_speed_duration:
                self.speed = self.stats['speed']
                self.vulnerable_speed = True
        # if not self.can_pick_thing:
        #     if current_time - self.pick_time >= self.pick_duration_cooldown:
        #         self.can_pick_thing = True

    def animate(self):
        animation = self.animations[self.status]

        # loop over the frame index
        self.frame_index += self.animation_speed
        if self.frame_index >= len(animation):
            self.frame_index = 0

        # set the image
        self.image = animation[int(self.frame_index)]
        self.rect = self.image.get_rect(center=self.hitbox.center)

        # flicker
        if not self.vulnerable:
            alpha = self.wave_value()
            self.image.set_alpha(alpha)
        else:
            self.image.set_alpha(255)

    def get_full_weapon_damage(self):
        base_damage = self.stats['attack']
        weapon_damage = weapon_data[self.weapon]['damage']
        return base_damage + weapon_damage

    def get_full_bullet_damage(self):
        return item_data['bullet']['damage']

    # thing
    def get_full_thing_recovery(self):
        recovery = item_data[self.thing]['recovery']
        return recovery

    def get_value_by_index(self, index):
        return list(self.stats.values())[index]

    def get_cost_by_index(self, index):
        return list(self.upgrade_cost.values())[index]

    # def energy_recovery(self):
    #     if self.energy < self.stats['energy']:
    #         self.energy += 0.01 * self.stats['magic']
    #     else:
    #         self.energy = self.stats['energy']

    def update(self):
        self.update_thing_list()
        self.input()
        self.cooldowns()
        self.show_caption()
        self.get_status()
        self.animate()
        self.move(self.speed)
        # self.energy_recovery()
        self.position()
        # x1800-1900
        # y2100-2250

