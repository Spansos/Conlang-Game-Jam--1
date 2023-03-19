import pygame as pg
import sys
import dataclasses

# this is taking too long, i'll just edit the level.txt's by hand


@dataclasses.dataclass
class Obstacle:
    rect: pg.Rect
    hazard: bool
    fixed: bool
    state: int




def main():
    window = pg.display.set_mode((800, 600))

    obs = []
    ob: Obstacle = None

    while True:
        for ev in pg.event.get():
            if ev.type == pg.QUIT:
                pg.quit()
                sys.exit()
            if ev.type == pg.MOUSEBUTTONDOWN and ev.button == 1:
                if ob:
                    ob.rect.width = 

        window.fill((32, 42, 64))
        for ob in obs:
            pg.draw.rect(window, (255,255,255), ob.rect)
        pg.display.update()

if __name__ == '__main__':
    main()