
#include <nds.h>
#include <gl2d.h>

void init3D() {
    videoSetMode(MODE_0_3D);
    vramSetBankA(VRAM_A_TEXTURE);

    glInit();
    glEnable(GL_ANTIALIAS);
    glClearColor(0, 0, 0, 31); // Sky color
    glClearPolyID(63); // Max polygon ID
    glClearDepth(0x7FFF);

    glEnable(GL_TEXTURE_2D);
    glEnable(GL_BLEND);
}

void drawCube(int x, int y, int z, int size) {
    glPushMatrix();
    glTranslatef(x, y, z);

    glBegin(GL_QUADS);
    glColor3f(1.0, 0.0, 0.0);
    glVertex3v16(inttof32(-size), inttof32(-size), inttof32(-size));
    glVertex3v16(inttof32( size), inttof32(-size), inttof32(-size));
    glVertex3v16(inttof32( size), inttof32( size), inttof32(-size));
    glVertex3v16(inttof32(-size), inttof32( size), inttof32(-size));
    glEnd();

    glPopMatrix(1);
}

int main(void) {
    int angle = 0;

    init3D();

    while (1) {
        scanKeys();
        int held = keysHeld();

        glLoadIdentity();
        glTranslatef(0, 0, -3 << 12); // Camera back
        glRotateY(angle);

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        drawCube(0, 0, 0, 1 << 11); // Draw player

        if (held & KEY_LEFT)  angle -= 2;
        if (held & KEY_RIGHT) angle += 2;

        glFlush(0);
        swiWaitForVBlank();
    }

    return 0;
}
