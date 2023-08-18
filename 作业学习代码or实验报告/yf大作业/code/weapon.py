import pygame


class Weapon(pygame.sprite.Sprite):
    def __init__(self, player, groups, shoot_bullet):
        super().__init__(groups)
        self.sprite_type = 'weapon'
        self.shoot_bullet = shoot_bullet
        direction = player.status.split('_')[0]
        # self.name
        # graphic
        full_path = f'../graphics/weapons/{player.weapon}/{direction}.png'
        self.image = pygame.image.load(full_path).convert_alpha()

        # placement
        if direction == 'right':
            self.rect = self.image.get_rect(midleft=player.rect.midright + pygame.math.Vector2(0, 16))
            # print(player.weapon)
            if player.weapon == 'gun':
                if player.player_bag['thing']['bullet'] >= 1:
                    self.shoot_bullet(player, self.rect.centerx, self.rect.centerx)
        elif direction == 'left':
            # print(player.weapon)
            self.rect = self.image.get_rect(midright=player.rect.midleft + pygame.math.Vector2(0, 16))
            if player.weapon == 'gun':
                if player.player_bag['thing']['bullet'] >= 1:
                    self.shoot_bullet(player, self.rect.centerx, self.rect.centerx)
        elif direction == 'down':
            # print(player.weapon)
            self.rect = self.image.get_rect(midtop=player.rect.midbottom + pygame.math.Vector2(-10, 0))
            if player.weapon == 'gun':
                if player.player_bag['thing']['bullet'] >= 1:
                    self.shoot_bullet(player, self.rect.centerx, self.rect.centerx)
        else:
            print(player.weapon)
            self.rect = self.image.get_rect(midbottom=player.rect.midtop + pygame.math.Vector2(-10, 0))
            if player.weapon == 'gun':
                if player.player_bag['thing']['bullet'] >= 1:
                    self.shoot_bullet(player, self.rect.centerx, self.rect.centerx)
