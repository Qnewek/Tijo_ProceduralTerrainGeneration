## Testowanie i jakość oprogramowania\
## Dawid Kusion\
## Testowanie funkcji proceduralnego generowani terenu

# Testy jednostkowe
## Test 1: biomeVerifyTest
### Given (Założenia)
•	Obiekt biome::Biome jest tworzony z określonymi parametrami: ID, nazwą, zakresami temperatury, wilgotności, kontynentalności i górzystości.
•	Ustawiane są wartości temperatury T, wilgotności H, kontynentalności C i górzystości M.
### When (Działania)
•	Wywoływana jest metoda verifyBiome z podanymi wartościami T, H, C i M.
### Then (Sprawdzenie)
•	Test sprawdza, czy podane wartości mieszczą się w zakresie określonym dla biomu za pomocą EXPECT_TRUE.

## Test 2: setBiomesTest
### Given (Założenia)
•	Tworzona jest pusta wektorowa lista biomów biomes.
•	Tworzony jest obiekt BiomeGenerator.
### When (Działania)
•	Wywoływana jest metoda setBiomes z pustą listą biomów.
### Then (Sprawdzenie)
•	Test sprawdza, czy metoda zwraca false dla pustej listy biomów za pomocą EXPECT_FALSE.

## Test 3: setRangesTest
### Given (Założenia)
•	Tworzona jest zagnieżdżona lista zakresów ranges dla różnych parametrów świata.
•	Tworzony jest obiekt BiomeGenerator.
•	Ustawiane są zakresy za pomocą metody setRanges.
•	Oczekiwana wartość poziomu dla wilgotności Humidity i wartości -1.5f wynosi -2.
### When (Działania)
•	Wywoływana jest metoda determineLevel z parametrem WorldParameter::Humidity i wartością -1.5f.
### Then (Sprawdzenie)
•	Test sprawdza, czy metoda zwraca oczekiwaną wartość poziomu za pomocą EXPECT_EQ.

## Test 4: adjustingVelocityTest
### Given (Założenia)
•	Początkowa prędkość kropli wynosi 1.0f.
•	Grawitacja wynosi 1.0f.
•	Różnica wysokości wynosi 0.2f.
•	Oczekiwana nowa prędkość jest obliczana jako sqrtf((velocity * velocity) + (elevationDiff * gravity)).
•	Tworzony jest obiekt erosion::Droplet z początkową pozycją (0.0f, 0.0f), prędkością 1.0f, wodą 1.0f i osadem 1.0f.
### When (Działania)
•	Wywoływana jest metoda adjustVelocity z różnicą wysokości i grawitacją.
•	Pobierana jest nowa prędkość kropli za pomocą getVelocity.
### Then (Sprawdzenie)
•	Test sprawdza, czy nowa prędkość kropli jest zgodna z oczekiwaną wartością za pomocą EXPECT_EQ.

## Test 5: dropSedimentTest
### Given (Założenia)
•	Różnica wysokości wynosi 0.5f.
•	Oczekiwana ilość osadu do zrzucenia wynosi 0.0f (domyślna wartość dla osadu, wynik min(elevationDiff, sediment)).
•	Tworzony jest obiekt erosion::Droplet z początkową pozycją (0.0f, 0.0f), prędkością 1.0f, wodą 1.0f i osadem 1.0f.
### When (Działania)
•	Wywoływana jest metoda dropSediment z różnicą wysokości.
•	Pobierana jest ilość zrzuconego osadu.
### Then (Sprawdzenie)
•	Test sprawdza, czy ilość zrzuconego osadu jest zgodna z oczekiwaną wartością za pomocą EXPECT_EQ.

## Test 6: evaporationTest
### Given (Założenia)
•	Wskaźnik parowania wynosi 0.01f.
•	Oczekiwana ilość wody po parowaniu wynosi 0.99f.
•	Tworzony jest obiekt erosion::Droplet z początkową pozycją (0.0f, 0.0f), prędkością 1.0f, wodą 1.0f i osadem 1.0f.
### When (Działania)
•	Wywoływana jest metoda evaporate z wskaźnikiem parowania.
•	Pobierana jest nowa ilość wody za pomocą getWater.
### Then (Sprawdzenie)
•	Test sprawdza, czy ilość wody po parowaniu jest zgodna z oczekiwaną wartością za pomocą EXPECT_EQ.

## Test 7: mapNullPtrInitializationTest
### Given (Założenia)
•	Oczekiwany wskaźnik mapy wynosi nullptr.
•	Tworzony jest obiekt erosion::Erosion z wymiarami 3x3.
### When (Działania)
•	Pobierany jest wskaźnik mapy za pomocą getMap.
### Then (Sprawdzenie)
•	Test sprawdza, czy wskaźnik mapy jest równy nullptr za pomocą EXPECT_EQ.

## Test 8: mapInitializationTest
### Given (Założenia)
•	Tworzona jest mapa o rozmiarze 9 (3x3).
•	Tworzony jest obiekt erosion::Erosion z wymiarami 3x3.
### When (Działania)
•	Ustawiana jest mapa za pomocą SetMap.
•	Pobierany jest wskaźnik mapy za pomocą getMap.
### Then (Sprawdzenie)
•	Test sprawdza, czy wskaźnik mapy nie jest równy nullptr za pomocą EXPECT_TRUE.
•	Usuwana jest mapa za pomocą delete[].

## Test 9: gradientTest
### Given (Założenia)
•	Początkowa pozycja wynosi (0.5f, 0.5f).
•	Oczekiwany gradient jest obliczany na podstawie różnic wysokości w mapie.
•	Tworzony jest obiekt erosion::Erosion z wymiarami 2x2.
•	Tworzona jest mapa o rozmiarze 4 z wartościami {0.40f, 0.70f, 0.20f, 0.40f}.
•	Ustawiana jest mapa za pomocą SetMap.
### When (Działania)
•	Wywoływana jest metoda getGradient z początkową pozycją.
•	Pobierany jest gradient.
### Then (Sprawdzenie)
•	Test sprawdza, czy gradient w osi x jest zgodny z oczekiwaną wartością za pomocą EXPECT_EQ.
•	Test sprawdza, czy gradient w osi y jest zgodny z oczekiwaną wartością za pomocą EXPECT_EQ.

## Test 10: isOnMapTest
### Given (Założenia)
•	Początkowa pozycja wynosi (3.0f, 3.0f).
•	Tworzony jest obiekt erosion::Erosion z wymiarami 2x2.
### When (Działania)
•	Wywoływana jest metoda isOnMap z początkową pozycją.
### Then (Sprawdzenie)
•	Test sprawdza, czy pozycja znajduje się poza mapą za pomocą EXPECT_FALSE.

Testy integracyjne
Test 1: positionTest
Given (Założenia)
•	Obiekt erosion::Erosion jest tworzony z wymiarami 3x3.
•	Mapa wysokości jest inicjalizowana z określonymi wartościami i ustawiana w obiekcie erosion.
•	Obiekt erosion::Droplet jest tworzony z początkową pozycją (0.9f, 0.9f) oraz innymi parametrami.
When (Działania)
•	Gradient w pozycji kropli jest obliczany za pomocą erosion.getGradient.
•	Kierunek kropli jest dostosowywany na podstawie gradientu.
•	Sprawdzane jest, czy nowa pozycja kropli nadal znajduje się na mapie za pomocą erosion.isOnMap.
Then (Sprawdzenie)
•	Test sprawdza, czy kropla nadal znajduje się na mapie za pomocą EXPECT_TRUE.

Test 2: dropletDisplacement
Given (Założenia)
•	Obiekt erosion::Erosion jest tworzony z wymiarami 4x4.
•	Mapa wysokości jest inicjalizowana z określonymi wartościami i ustawiana w obiekcie erosion.
•	Obiekt erosion::Droplet jest tworzony z początkową pozycją (1.6f, 1.2f) oraz innymi parametrami.
•	Osad kropli jest dostosowywany o 0.5f.
•	Oczekiwany osad do zebrania wynosi 0.05f.
•	Oczekiwana nowa pozycja kropli to (1.15f, 0.3f).
When (Działania)
•	Gradient w pozycji kropli jest obliczany za pomocą erosion.getGradient.
•	Stara pozycja kropli jest zapisywana.
•	Kierunek kropli jest dostosowywany na podstawie gradientu.
•	Różnica wysokości między starą a nową pozycją jest obliczana.
•	Osad do zebrania jest obliczany na podstawie różnicy wysokości.
Then (Sprawdzenie)
•	Test sprawdza, czy zebrany osad jest zbliżony do oczekiwanej wartości za pomocą EXPECT_NEAR.
•	Test również sprawdza, czy nowa pozycja kropli jest zbliżona do oczekiwanej pozycji za pomocą EXPECT_NEAR.
Given (Założenia)
•	Obiekt TerrainGenerator jest tworzony.
•	Ustawiane są wymiary mapy na 10x10 oraz rozdzielczość chunków na 10.
When (Działania)
•	Wywoływana jest metoda initializeMap.
Then (Sprawdzenie)
•	Test sprawdza, czy mapa została poprawnie zainicjalizowana za pomocą EXPECT_TRUE.

Test 1: initializeMapTest
Given (Założenia)
•	Obiekt TerrainGenerator jest tworzony.
•	Ustawiane są wymiary mapy na 10x10 oraz rozdzielczość chunków na 10.
When (Działania)
•	Wywoływana jest metoda initializeMap.
Then (Sprawdzenie)
•	Test sprawdza, czy mapa została poprawnie zainicjalizowana za pomocą EXPECT_TRUE.

Test 4: heightMapGenerationTest
Given (Założenia)
•	Obiekt TerrainGenerator jest tworzony i konfigurowany z wymiarami 10x10, rozdzielczością chunków 5 oraz seedem 742.
•	Konfigurowane są parametry szumów dla różnych typów terenu.
•	Ustawiane są splajny dla różnych typów terenu.
•	Oczekiwana wartość wysokości w punkcie (0, 0) wynosi 457877 (po zaokrągleniu i przeliczeniu na int).
When (Działania)
•	Wywoływana jest metoda generateHeightMap.
•	Pobierana jest wysokość w punkcie (0, 0) i przeliczana na int.
Then (Sprawdzenie)
•	Test sprawdza, czy mapa wysokości została poprawnie wygenerowana za pomocą EXPECT_TRUE.
•	Test sprawdza, czy wysokość w punkcie (0, 0) jest zgodna z oczekiwaną wartością za pomocą EXPECT_EQ.

Test 5: biomeMapGenerationTest
Given (Założenia)
•	Obiekt TerrainGenerator jest tworzony i konfigurowany z wymiarami 10x10, rozdzielczością chunków 5 oraz seedem 742.
•	Konfigurowane są parametry szumów dla różnych typów terenu.
•	Ustawiane są splajny dla różnych typów terenu.
•	Ustawiane są biomy oraz ich zakresy.
•	Oczekiwany biom w punkcie (3, 3) wynosi 5.
When (Działania)
•	Wywoływana jest metoda generateBiomes.
•	Pobierany jest biom w punkcie (3, 3).
Then (Sprawdzenie)
•	Test sprawdza, czy mapa biomów została poprawnie wygenerowana za pomocą EXPECT_TRUE.
•	Test sprawdza, czy biom w punkcie (3, 3) jest zgodny z oczekiwaną wartością za pomocą EXPECT_EQ.

Test 6: vegetationGeneratorTest
Given (Założenia)
•	Obiekt TerrainGenerator jest tworzony i konfigurowany z wymiarami 10x10, rozdzielczością chunków 5 oraz seedem 742.
•	Konfigurowane są parametry szumów dla różnych typów terenu.
•	Ustawiane są splajny dla różnych typów terenu.
•	Ustawiane są biomy oraz ich zakresy.
•	Oczekiwane współrzędne roślinności w punkcie (2, 4) wynoszą (11, 3).
•	Oczekiwana liczba drzew wynosi 137.
When (Działania)
•	Wywoływana jest metoda performTerrainGeneration.
•	Pobierane są punkty roślinności oraz liczba drzew.
Then (Sprawdzenie)
•	Test sprawdza, czy generowanie roślinności zostało poprawnie wykonane za pomocą EXPECT_TRUE.
•	Test sprawdza, czy współrzędne roślinności w punkcie (2, 4) są zgodne z oczekiwanymi wartościami za pomocą EXPECT_EQ.
•	Test sprawdza, czy liczba drzew jest zgodna z oczekiwaną wartością za pomocą EXPECT_EQ.

Test 7: nosieGenerationTest
Given (Założenia)
•	Obiekt noise::SimplexNoiseClass jest tworzony i konfigurowany z seedem 742 oraz rozmiarem mapy 10x10.
•	Oczekiwana wartość szumu w punkcie (7, 7) wynosi 0.16376.
When (Działania)
•	Wywoływana jest metoda generateFractalNoiseByChunks.
•	Pobierana jest wartość szumu w punkcie (7, 7).
Then (Sprawdzenie)
•	Test sprawdza, czy generowanie szumu zostało poprawnie wykonane za pomocą EXPECT_NEAR.

Test 8: nonValidMapGenTest
Given (Założenia)
•	Obiekt TerrainGenerator jest tworzony.
•	Ustawiane są wymiary mapy na 10x10 oraz rozdzielczość chunków na 10.
When (Działania)
•	Wywoływana jest metoda generateHeightMap.
Then (Sprawdzenie)
•	Test sprawdza, czy generowanie mapy wysokości nie powiodło się za pomocą EXPECT_FALSE.

Test 9: nonValidBiomeGenTest
Given (Założenia)
•	Obiekt TerrainGenerator jest tworzony.
•	Ustawiane są wymiary mapy na 10x0 oraz rozdzielczość chunków na 10.
When (Działania)
•	Wywoływana jest metoda generateBiomes.
Then (Sprawdzenie)
•	Test sprawdza, czy generowanie biomów nie powiodło się za pomocą EXPECT_FALSE.

Test 10: nonValidAverageBiomeCalculationTest
Given (Założenia)
•	Obiekt TerrainGenerator jest tworzony i konfigurowany z wymiarami 10x10, rozdzielczością chunków 5 oraz seedem 742.
•	Konfigurowane są parametry szumów dla różnych typów terenu.
•	Ustawiane są splajny dla różnych typów terenu.
•	Ustawiane są biomy oraz ich zakresy.
When (Działania)
•	Wywoływana jest metoda initializeMap.
•	Ustawiane są biomy oraz ich zakresy.
•	Wywoływana jest metoda generateBiomes.
•	Wywoływana jest metoda deinitalizeBiomeMap.
•	Wywoływana jest metoda generateBiomeMapPerChunk.
Then (Sprawdzenie)
•	Test sprawdza, czy generowanie mapy biomów na chunkach nie powiodło się za pomocą EXPECT_FALSE.
