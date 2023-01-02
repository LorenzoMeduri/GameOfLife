#include <SFML/Graphics.hpp>
#include <iostream>
#include <ctime>

using namespace std;
using namespace sf;


bool mat[216][384],vis[216][384];
short celleVive(short i,short j);
void generazioneCelle();
void confronto();
int main()
{
    short delay = 20,tempoTrascorso = 0;
    bool mod;
    Clock clock;
    Time now;

    srand(time(NULL));

    cout<<"Vuoi passare di generazione con spazio(0) o con un delay(1)? ";
    cin>>mod;

    if(mod){        //se l'utente ha scelto l'opzione con il delay glielo viene fatto inserire
        cout<<"Inserisci il delay tra ogni generazione(millisecondi): ";
        cin>>delay;
        delay/=10;
    }


    RenderWindow finestra(VideoMode(1920,1080),"Game of Life di Lorenzo Meduri",Style::Fullscreen | Style::Close); //apro la nuova finestra

    Texture textureViva;

    textureViva.loadFromFile("./Texture/cella_viva.png");  //carico la texture

    Sprite spriteViva;

    spriteViva.setTexture(textureViva);     //associo alla spriteViva la sua texture

    generazioneCelle();        //genero la prima matrice di celle

    while(finestra.isOpen()){
        Event evento;

        while(finestra.pollEvent(evento)){ // abilito il tasto della chiusura
            if(evento.type == Event::Closed)
                finestra.close();
        }
        finestra.clear(Color::Black);   // cancello il contenuto della finestra prima di mostrarne un'altro


        for(short i=0;i<215;i++) // ciclo per visualizzare la matrice di celle
            for(short j=0;j<383;j++)
                if(vis[i][j]){
                    spriteViva.setPosition(Vector2f(j*5,i*5));
                    finestra.draw(spriteViva);
                }

        finestra.display();    //mostro il contenuto

        now = clock.getElapsedTime();   // creo una variabile in cui inserisco ad ogni ciclo il tempo corrente

        if(mod){    // scelgo la modalità inserita dall'utente
            if((now.asMilliseconds()/10 >= tempoTrascorso + delay) && finestra.hasFocus()){ // per cambiare la matrice deve essere trascorso il delay
                confronto();                                                                // e l'utente deve essere sulla finsestra
                tempoTrascorso = now.asMilliseconds()/10;
            }
        }else{
            if((now.asMilliseconds()/10 >= tempoTrascorso + delay) && finestra.hasFocus() && (Keyboard::isKeyPressed(Keyboard::Space))){
                confronto();                                                             //questo ciclo è come quello precedente ma in più l'utente
                tempoTrascorso = now.asMilliseconds()/10;                                //deve cliccare spazio con un delay prefissato a 300 ms
            }
        }
    }
    return 0;
}
void confronto(){
    short vive=0;
    for(short i=0;i<215;i++)     //cambio la matrice in base alle sue celle vicine usando la funzione "celleVive"
        for(short j=0;j<383;j++){
            vive = celleVive(i,j);
            if(mat[i][j]){
                if(vive == 2 || vive == 3){
                    vis[i][j] = true;
                }
                else
                    vis[i][j] = false;
            }else{
                if(vive == 3)
                    vis[i][j] = true;
                else
                    vis[i][j] = false;
            }
        }

    for(short i=0;i<215;i++)
        for(short j=0;j<383;j++)
            if(vis[i][j])
                mat[i][j] = true;
            else
                mat[i][j] = false;
}
void generazioneCelle(){      //genero la prima matrice di celle in modo casuale
    for(short i=0;i<215;i++)
        for(short j=0;j<383;j++){
            mat[i][j] = rand()%2;
            vis[i][j] = mat[i][j];
        }
}
short celleVive(short i,short j){       //funzione che calcola le celle vive adiacenti per ogni cella
                                        // con delle condizioni diverse in base alla sua posizione
    short celleVive=0;
    if(i == 0 && j == 0 ){              // angolo in alto a sinistra
        if(mat[i+1][j])
            celleVive++;
        if(mat[i+1][j+1])
            celleVive++;
        if(mat[i][j+1])
            celleVive++;
    }
    if(i == 0 && j != 384 && j != 0){    // lato in alto
        if(mat[i][j-1])
            celleVive++;
        if(mat[i+1][j-1])
            celleVive++;
        if(mat[i+1][j])
            celleVive++;
        if(mat[i+1][j+1])
            celleVive++;
        if(mat[i][j+1])
            celleVive++;
    }
    if(i == 0 && j == 384){ // angolo in alto a destra
        if(mat[i][j-1])
            celleVive++;
        if(mat[i+1][j-1])
            celleVive++;
        if(mat[i+1][j])
            celleVive++;
    }
    if(j == 384 && i != 0 && i != 216){   //lato a destra
        if(mat[i-1][j])
            celleVive++;
        if(mat[i-1][j-1])
            celleVive++;
        if(mat[i][j-1])
            celleVive++;
        if(mat[i+1][j-1])
            celleVive++;
        if(mat[i+1][j])
            celleVive++;
    }
    if(i == 216 && j == 384){ // angolo in basso a destra
        if(mat[i-1][j])
            celleVive++;
        if(mat[i-1][j-1])
            celleVive++;
        if(mat[i][j-1])
            celleVive++;
    }
    if(i == 216 && j != 384 && j != 0){   // lato in basso
        if(mat[i-1][j])
            celleVive++;
        if(mat[i-1][j-1])
            celleVive++;
        if(mat[i][j-1])
            celleVive++;
        if(mat[i-1][j+1])
            celleVive++;
        if(mat[i][j+1])
            celleVive++;
    }
    if(i == 216 && j == 0){ // angolo in basso a sinistra
        if(mat[i-1][j])
            celleVive++;
        if(mat[i-1][j+1])
            celleVive++;
        if(mat[i][j+1])
            celleVive++;
    }
    if(j == 0 && i != 216 && i != 0){    // lato a sinistra
        if(mat[i-1][j])
            celleVive++;
        if(mat[i-1][j+1])
            celleVive++;
        if(mat[i][j+1])
            celleVive++;
        if(mat[i+1][j+1])
            celleVive++;
        if(mat[i+1][j])
            celleVive++;
    }
    if(i > 0 && j > 0 && i < 216 && j < 384){ // condizione generale in cui la cella
        if(mat[i-1][j])                     // non è adiacente ad un bordo
            celleVive++;
        if(mat[i-1][j+1])
            celleVive++;
        if(mat[i][j+1])
            celleVive++;
        if(mat[i+1][j+1])
            celleVive++;
        if(mat[i+1][j])
            celleVive++;
        if(mat[i+1][j-1])
            celleVive++;
        if(mat[i][j-1])
            celleVive++;
        if(mat[i-1][j-1])
            celleVive++;
    }
    return celleVive;
}
