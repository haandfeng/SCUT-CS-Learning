import pygame
from settings import *
from entity import Entity
from support import *


class Thing(Entity):
    def __init__(self, thing_name, pos, groups):
        # general setup
        super().__init__(groups)
        self.sprite_type = 'thing'

        # stats

        self.thing_name = thing_name
        # 注意thing的数据叫item_Data
        thing_info = item_data[self.thing_name]
        # self.health = monster_info['health']
        # self.exp = monster_info['exp']
        # self.speed = monster_info['speed']
        # self.attack_damage = trap_info['damage']
        # self.attack_type = trap_info['attack_type']
        # self.resistance = monster_info['resistance']
        # self.attack_radius = monster_info['attack_radius']
        # self.notice_radius = monster_info['notice_radius']

        # graphics setup  draw picture once init the trap
        self.image = pygame.image.load(item_data[thing_name]['graphic']).convert_alpha()

        # self.image = self.animations[self.status][self.frame_index]
        self.rect = self.image.get_rect(topleft=pos)
        self.hitbox = self.rect

        # player interaction
        # self.can_attack = True
        # self.attack_time = None
        # self.attack_cooldown = 400

        # damage
        # self.trap_damage_player = trap_damage_player
        # self.trigger_death_particles = trigger_death_particles
        # # invincibility timer
        # self.vulnerable = True
        # self.hit_time = None
        # self.invincibility_duration = 300

        # # sounds
        # self.death_sound = pygame.mixer.Sound('../audio/death.wav')
        # self.hit_sound = pygame.mixer.Sound('../audio/hit.wav')
        # self.attack_sound = pygame.mixer.Sound(monster_info['attack_sound'])
        # self.death_sound.set_volume(0.6)
        # self.hit_sound.set_volume(0.6)
        # self.attack_sound.set_volume(0.6)

    def import_graphics(self, name):
        # self.animations = {'idle': [], 'move': [], 'attack': []}

        return f'../graphics/trap/{name}/'

        # for animation in self.animations.keys():
        #     self.animations[animation] = import_folder(main_path + animation)

    #  check collide
    def thing_collision(self, player):

        if self.hitbox.colliderect(player.hitbox):
            return True
        return False

    def actions(self, player):
        # 如果产生碰撞 检查和player的碰撞
        if self.trap_collision(player):
            self.attack_time = pygame.time.get_ticks()
            self.trap_damage_player(self.attack_damage, self.trap_name)
            # self.attack_sound.play()

    def cooldowns(self):
        current_time = pygame.time.get_ticks()
        if not self.can_attack:
            if current_time - self.attack_time >= self.attack_cooldown:
                self.can_attack = True

    def damage(self):
        self.kill()

    def update(self):
        pass
        # self.cooldowns()

    def thing_update(self, player):
        pass
        # self.actions(player)

    #
    # def enemy_update(self, player):
    #     self.get_status(player)
    #     self.actions(player)
