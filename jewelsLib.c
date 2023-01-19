#include "jewelsLib.h"


long frames;
long score;

ALLEGRO_FONT* font;
long score_display;

int between(int min, int max)
{
    return (rand() % (max - min)) + min;
}

float betweenf(float min, float max)
{
    return ((float)rand() / (float)RAND_MAX) * (max-min) + min;
}


void hud_init()
{
    font = al_create_builtin_font();
    mustInit(font, "font"); 

    score_display = 0;
}

void hud_deinit()
{
    al_destroy_font(font);
}

void hud_update()
{
    if(frames % 2)
        return;
    
    for(long i = 5; i>0; i--)
    {
        long diff = 1 << i;
        if(score_display <= (score - diff))
            score_display += diff;
    }
}

int linear_combination(MATRIX** m, int i, int j){
    
    if((m[i][j].type == m[i][j+1].type)||(m[i][j].type == m[i][j-1].type)){
        return 1;
    }

    return 0;

}

int vertical_combination(MATRIX** m, int i, int j){

    if((m[i][j].y == 0)||(m[i][j].y == 380)){
        return 0;
    }
    if(m[i][j].type == m[i-1][j].type){
        return 1;
    }
    return 0;

}

MATRIX** matrix_init(int size)
{
    int dx = 380;
    int dy = 0;
    // Create a size x size matrix
    MATRIX** m = malloc(sizeof(MATRIX*) * size);
    mustInit(m, "matrix");
    for(int i = 0; i < size; i++)
    {
        m[i] = malloc(sizeof(MATRIX) * size);
        mustInit(m[i], "matrix");

        for(int j = 0; j < size; j++)
        {
            m[i][j].select[0] = 0;
            m[i][j].select[1] = 0;
            m[i][j].x = DISP_W/2 - dx;
            m[i][j].y = dy;
            m[i][j].type = rand() % 5;

            printf("i: %d, j: %d", i, j);

            while((linear_combination(m, i, j))||(vertical_combination(m, i, j)))
                m[i][j].type = rand() % 5;
            
            dx -= 30;
        }
        dx = 380;
        dy += 30;
    }
    return m;
}

void matrix_deinit(MATRIX** m, int size)
{
    for(int i = 0; i < size; i++)
        free(m[i]);
    free(m);
}

void matrix_draw(MATRIX** matrix)
{
    for(int i = 0; i < MATRIX_SIZE; i++)
        {
            for(int j = 0; j < MATRIX_SIZE; j++)
            {
                switch (matrix[i][j].type)
                {
                case 0:
                    al_draw_bitmap(sprites.green, matrix[i][j].x, matrix[i][j].y, 0);
                    break;
                case 1:
                    al_draw_bitmap(sprites.blue, matrix[i][j].x, matrix[i][j].y, 0);
                    break;
                case 2:
                    al_draw_bitmap(sprites.red, matrix[i][j].x, matrix[i][j].y, 0);
                    break;
                case 3:
                    al_draw_bitmap(sprites.yellow, matrix[i][j].x, matrix[i][j].y, 0);
                    break;
                case 4:
                    al_draw_bitmap(sprites.purple, matrix[i][j].x, matrix[i][j].y, 0);
                    break;
                
                default:
                    break;
                }
            }
        }
}

void hud_draw()
{

    al_draw_textf(font, al_map_rgb_f(1, 1, 1), 54, 50, 0, "%06ld", score_display); 
    al_draw_filled_rectangle(DISP_W/2 - 360, 15, DISP_W/2 - 40, 325, al_map_rgb(0, 0, 0));
    al_draw_filled_rectangle(DISP_W/2 - 370, 10, DISP_W/2 - 50, 315, al_map_rgb(219, 218, 222));

    al_draw_text(font, al_map_rgb(20, 179, 20), 10, 10, 0, "< T E R M O I L >");
    
}

void help_draw()
{
        al_draw_text(font, al_map_rgb(20, 179, 20), DISP_W/4, 10, ALLEGRO_ALIGN_CENTRE, "< T E R M O I L >");
        al_draw_text(font, al_map_rgb(20, 179, 20), DISP_W/4, 30, ALLEGRO_ALIGN_CENTRE, "F1 ou H - menu de ajuda");
        al_draw_text(font, al_map_rgb(20, 179, 20), DISP_W/4, 50, ALLEGRO_ALIGN_CENTRE, "Como jogar:");
        al_draw_text(font, al_map_rgb(20, 179, 20), DISP_W/4, 70, ALLEGRO_ALIGN_CENTRE, "Clique em duas peças para troca-las de lugar");
        al_draw_text(font, al_map_rgb(20, 179, 20), DISP_W/4, 90, ALLEGRO_ALIGN_CENTRE, "Combine 3 ou mais peças do mesmo tipo para eliminá-las");
        al_draw_text(font, al_map_rgb(20, 179, 20), DISP_W/4, 110, ALLEGRO_ALIGN_CENTRE, "Quanto mais peças você eliminar de uma vez, mais pontos você ganha");


}