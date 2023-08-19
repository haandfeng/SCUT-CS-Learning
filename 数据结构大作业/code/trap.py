import pygame
from settings import *
from entity import Entity
from support import *


class Trap(Entity):
    def __init__(self, trap_name, pos, groups, trap_damage_player):
        # general setup
        super().__init__(groups)
        self.sprite_type = 'trap'

        # stats

        self.trap_name = trap_name
        trap_info = trap_data[self.trap_name]
        # self.health = monster_info['health']
        # self.exp = monster_info['exp']
        # self.speed = monster_info['speed']
        self.attack_damage = trap_info['damage']
        self.attack_type = trap_info['attack_type']
        self.attack_speed = trap_info['speed']
        # self.resistance = monster_info['resistance']
        # self.attack_radius = monster_info['attack_radius']
        # self.notice_radius = monster_info['notice_radius']

        # graphics setup  draw picture once init the trap
        self.image = pygame.image.load(trap_data[trap_name]['graphic']).convert_alpha()

        # self.image = self.animations[self.status][self.frame_index]
        self.rect = self.image.get_rect(topleft=pos)
        self.hitbox = self.rect

        # player interaction
        self.can_attack = True
        self.attack_time = None
        self.attack_cooldown = 400

        # damage
        self.trap_damage_player = trap_damage_player
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
    def trap_collision(self, player):

        if self.hitbox.colliderect(player.hitbox):
            return True
        return False

    def actions(self, player):
        # 如果产生碰撞 检查和player的碰撞
        if self.trap_collision(player) and self.attack_type == 'health':
            self.attack_time = pygame.time.get_ticks()
            self.trap_damage_player(self.attack_damage, self.trap_name)
            # self.attack_sound.play()
        elif self.trap_collision(player) and self.attack_type == 'speed':
            self.attack_time = pygame.time.get_ticks()
            self.trap_damage_player(self.attack_speed, self.trap_name)

    def cooldowns(self):
        current_time = pygame.time.get_ticks()
        if not self.can_attack:
            if current_time - self.attack_time >= self.attack_cooldown:
                self.can_attack = True

    def get_damage(self):
        pass

    def update(self):
        self.cooldowns()

    def trap_update(self, player):
        self.actions(player)

    #
    # def enemy_update(self, player):
    #     self.get_status(player)
    #     self.actions(player)
