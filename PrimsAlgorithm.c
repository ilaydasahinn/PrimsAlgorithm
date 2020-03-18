#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#define MELKOR 1000000
 
 
//Matrisimizi tutacağımzı dizi
int Array[5][5];
 
//Matrisimizi matris.txt dosyasından okuyup dizimize aktaran fonksiyon
void readMatrix()
{
    int i = 0;
    FILE *fp = fopen("prims.txt", "r");
 
    while(fscanf(fp, "%d %d %d %d %d",
                 &Array[i][0],
                 &Array[i][1],
                 &Array[i][2],
                 &Array[i][3],
                 &Array[i][4]
                 ) != EOF)
    {
        i = i + 1 ;
    }
}
 
//En kısa yolun indisini geri döndüren yardımcı fonksiyon..
int minKey(int key[], bool visited[])
{
    int min = MELKOR;
    int minIndex, i;
    for( i = 0; i < 5; i++)
    {
        //Eğer bir düğüm ziyaret edilmemiş ve min değerinden daha küçükse burayı seçiyoruz.
        if(visited[i] == false && key[i] < min)
        {
            min = key[i];
            minIndex = i;
            }
    }
    //minIndex'i return ediyoruz.
    return minIndex;
}
 
//Esas fonksiyon burada, veri yapımızı tutan diziyi parametre olarak veriyoruz.
void prims(int Array[5][5])
{
    //Genel değişkenler
    int i, j, t;
    int key[5];
    int parent[5];
    bool visited[5];
 
    //Tüm düğümleri ziyaret edilmemiş olarak işaretleyip, maliyeti sonsuz yapıyoruz.
    for(i = 0; i < 5; i++)
    {
        visited[i] = false;
        key[i] = MELKOR;
    }
 
    //Başlangıç düğümünü belirliyoruz. Parentı olmadığı için -1 veriyoruz.
    key[0] = 0;
    parent[0] = -1;
 
    //5 düğümümüz olduğu için dış döngümüz 5 defa dönecek
    for(j = 0; j < 5; j++)
    {
        //En kısa yolu u değerine atıyoruz
        int u = minKey(key, visited);
        //Ziyaret edildi olarak işaretliyoruz.
        visited[u] = true;
 
        //Fonksiyonun can damarı
        for(t = 0; t < 5; t++)
        {
            //En az maliyete sahip ziyaret edilmemiş düğümü ekliyoruz.
            if(Array[u][t] && visited[t] == false && Array[u][t] < key[t])
            {
                key[t] = Array[u][t];
                parent[t] = u;
            }
        }
    }
    printMST(parent, Array);
 
}
 
int printMST(int parent[], int Array[5][5])
{
   int i;
   for (i = 1; i < 5; i++)
      printf("%d - %d    %d \n", parent[i], i, Array[i][parent[i]]);
}
 
int main()
{
    readMatrix();
    prims(Array);
}