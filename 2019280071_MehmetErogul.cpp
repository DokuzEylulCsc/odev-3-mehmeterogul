// Mehmet Erogul - 2019280071 //

#include <iostream>
#include <fstream>

using namespace std;

int main()
{
	//  ###### input.txt dosyasindaki verileri cekme asamasi. ######  //
	
	ifstream girdiDosyasi;
	int soruSayisi;
	int ogrenciSayisi;
	
	girdiDosyasi.open("input.txt");
	
	girdiDosyasi >> soruSayisi; // input.txt dosyamizin en ust satirindan soru sayisi verisini cekiyoruz.
	string cevapAnahtari[soruSayisi] = {}; // Cevap anahtarini cekmek icin soru sayisi buyuklugunde bir dizi olusturuyoruz.
	
	/* input.txt dosyamizin ikinci satirindan dongu yardimiyla cevap anahtarini cekiyor, ve cevapAnahtari dizimizin indislerine yerlestiriyoruz. */
	for (int i=0; i<soruSayisi; i++)
	{
		girdiDosyasi >> cevapAnahtari[i];
	}
	
	girdiDosyasi >> ogrenciSayisi; // input.txt dosyamizin 3. satirindaki ogrenci sayisi verisini cekiyoruz.
	/* (Ogrenci cevaplarini bir matriste toplamayi amacladim. Matrisin satir boyutunu elle vermek istemedim.
	Dolayisiyla input.txt dosyasinin 3. satirini ekstradan ogrenci sayisi verisini tutmak icin kullandim.)
	Bu veri hem matrisin yuksekligini belirlemede yardimci olacak hem de asagida kullanacak oldugum ic ice dongude faydali olacak. */
	
	string ogrenciBilgileri [ogrenciSayisi][soruSayisi+1] = {}; // Ogrenci cevaplarini tutmak icin olusturdugum matris.
	
	// Verilerimizi olusturdugumuz matrise ic ice donguler yardimiyla yerlestiriyoruz.
	for (int i=0; i<ogrenciSayisi; i++)
	{
		for (int j=0; j<(soruSayisi+1); j++)
		{
			girdiDosyasi >> ogrenciBilgileri [i][j];
		}
	}
	
	
	//  ###### Cekilen verileri isleme asamasi. ######  //
	
	// --------- Ogrencilerin notlarini hesaplama. ---------- //
	
	int ogrenciNotlari[ogrenciSayisi] = {}; // Ogrencilerin notlarini tutacak olan dizi. Dizinin boyutu ogrenci sayisi kadar olacak.
	
	// Ogrencilerin aldigi puaný hesaplayacak olan donguler.
	for (int i=0; i<ogrenciSayisi; i++) // Ogrenci cevap matrisinin satirlarini temsil eden dongu.
	{
		int ogrNot = 0; // Ogrencilerin notunu hesaplamak icin gecici bir degisken tanimliyor ve bunu dongu her dondugunde sifirliyoruz.
		for (int j=0; j<soruSayisi; j++)// Ogrenci cevap matrisinin sutunlarini temsil eden dongu.
		{
			/* Ogrencilerin verdigi cevaplari; ogrenciBilgileri ve cevapAnahtari dizilerini karsilastirarak kontrol edecegiz. */
			
			if (ogrenciBilgileri[i][j+1] == cevapAnahtari[j]) // Matrisin ilk sutunu ogrenci numarasini temsil ettigi icin bu sutunu j+1 kosulu kullanarak atliyoruz.
			ogrNot = ogrNot + 4; // Ogrencinin verdigi cevap dogruysa notu 4 puan artacak.
			
			else if (ogrenciBilgileri[i][j+1] == "x") // Bos cevaplar input.txt dosyamizda x harfi ile temsil ediliyor.
			ogrNot = ogrNot + 0; // Ogrencinin verdigi cevap bos ise notunda herhangi bir degisiklik olmayacak.
			
			else
			ogrNot = ogrNot - 1; // Ogrencinin verdigi cevap yanlis ise notu 1 puan azalacak.
			
			if (ogrNot<0) // Ogrencinin notu sýfýrdan kucuk ise; notu sifir olarak kabul edilecek.
			ogrNot = 0;
		}
		ogrenciNotlari[i] = ogrNot; // Ogrencilerin notlarini tutan dizimizin indislerine, ogrencilerin aldigi notlari yerlestiriyoruz.
	}
	
	// --------- Ogrencilerin notlarini 100'luk sisteme normalize etme. ---------- //
	
	int maksimumPuan = (soruSayisi*4);
	for (int i=0; i<ogrenciSayisi; i++)
	{
		// Bu kisimda dogru oranti uygulayarak ogrencinin aldigi notu 100'luk sistem uzerine normalize ettim.
		// (Ogrencinin aldigi puan) * 100 = x * maksimumPuan
		// x = ( (Ogrencinin aldigi puan) * 100) / maksimumPuan
		ogrenciNotlari[i] = (ogrenciNotlari[i] * 100) / maksimumPuan;
	}
	
	// --------- En kucuk ve en buyuk notu bulma. ---------- //
	
	// En kucuk ve en buyuk notlari bulmak icin ogrenciNotlari dizimizin indislerini teker teker karsilastiriyoruz.
	// Baslangicta enBuyukNot ve enKucukNot adinda iki degisken tanimliyoruz ve bu degiskenlerin degerine sifir atiyoruz.
	int enBuyukNot = 0;
	int enKucukNot = 0;
	
	for (int i=0; i<(ogrenciSayisi-1); i++)
	{
		// Notlari tutan dizimizde bir indisin kendisinden sonraki indisten buyuk mu yoksa kucuk mu oldugunu denetliyoruz.
		// Buyuk veya kucuk ise bunu enBuyukNot ve enKucukNot degiskenleriyle tekrar karsilastiriyoruz. Sonucunda en kucuk ve en buyuk not degerlerini buluyoruz.
		if (ogrenciNotlari[i] > ogrenciNotlari[i+1])
		{
			if (enBuyukNot < ogrenciNotlari[i])
			enBuyukNot = ogrenciNotlari[i];
		}
		
		if (ogrenciNotlari[i] < ogrenciNotlari[i+1])
		{
			if (enKucukNot > ogrenciNotlari[i])
			enKucukNot = ogrenciNotlari[i];
		}
	}
	
	// --------- Notlarin acikligini hesaplama. ---------- //
	
	int notAciklik = enBuyukNot - enKucukNot;
	
	// --------- Notlarin ortalamalarini hesaplama. ---------- //
	
	int ortalamaNot = 0;
	for (int i = 0; i < ogrenciSayisi; i++)
	{
		ortalamaNot += ogrenciNotlari[i];
	}
	ortalamaNot = ortalamaNot / ogrenciSayisi;
	
	
	//  ###### Verileri siralama asamasi. ######  //
	
	// Bubble sort siralama algoritmasiyla notlar dizimizdeki verileri kucukten buyuge dogru siraliyoruz.
	for(int i = 0; i < ogrenciSayisi; i++)
	{
    	for(int j = 0; j < ogrenciSayisi-1; j++)
		{  
			if(ogrenciNotlari[i] < ogrenciNotlari[j])
			{  
				// Ogrenci notlarini siraladigimiz kisim.
                int tutucu;
                tutucu = ogrenciNotlari[j];
                ogrenciNotlari[j] = ogrenciNotlari[i];
                ogrenciNotlari[i] = tutucu;
                
                /* ogrenciBilgileri matrisimizdeki her satir bilgisi, ogrenciNotlari dizimizin her bir indisine karsilik geliyor.
                Yani ayni ogrencinin bilgilerini tutuyor.
				Bu sebeple ogrenciNotlari dizisini siralarken ayni zamanda ogrenciBilgileri masrisini de siraliyoruz.
				Ogrencilerin soru cevap siklari bilgilerini degistirmek icin yeni bir dongu olusturuyoruz.
				Bu sayede matrisimizi de siralamis oluyoruz. */
                for (int k = 0; k < (soruSayisi + 1) ; k++)
                {
                	string tutucu2;
                	tutucu2 = ogrenciBilgileri[j][k];
               		ogrenciBilgileri[j][k] = ogrenciBilgileri[i][k];
                	ogrenciBilgileri[i][k] = tutucu2;
				}
            }
        }
    }
    
    // --------- Notlarin medyanini hesaplama. ---------- //
    
    int notMedyan = 0;
	// Ogrenci sayisi tek(notlari tutan dizinin boyutu tek) ise medyan -> (ogrenciSayisi+1)/2
	if (ogrenciSayisi % 2 == 1)
		notMedyan = ogrenciNotlari[((ogrenciSayisi + 1) / 2)-1]; // Dizi indisi 0'dan basladigi icin deger ayrica 1 eksiltildi.
	// Ogrenci sayisi çift(notlari tutan dizinin boyutu çift) ise medyan  -> ( (ogrenciSayisi/2) + ((ogrenciSayisi/2)+1) ) /2
	else
		notMedyan = ( ogrenciNotlari[(ogrenciSayisi/2)-1] + ogrenciNotlari[ogrenciSayisi/2] ) / 2;
	
	girdiDosyasi.close();
	
	
	//  ###### output.txt dosyasi olusturma asamasi. ######  //
	
	ofstream ciktiDosyasi;
	ciktiDosyasi.open("output.txt");
	
	// Siralanan ogrenci notlari ve bilgilerini dongu araciligiyla output.txt dosyasina yazdiriyoruz.
	for (int i = (ogrenciSayisi-1); i>=0; i--)
	{
		ciktiDosyasi << ogrenciBilgileri[i][0] << ",";
		ciktiDosyasi << ogrenciNotlari[i] << endl;
	}
	
	// Sirasiyla en kucuk not, en buyuk not, notlarin ortalamasi, medyan ve aciklik bilgilerini yazdiriyoruz.
	ciktiDosyasi << enBuyukNot << "," << enKucukNot << "," << ortalamaNot << "," << notMedyan << "," << notAciklik;
	
	cout <<endl << "output.txt dosyasi hazirlandi. Lutfen kontrol ediniz." << endl;
	
	ciktiDosyasi.close();
	
	return 0;
}
