#include "midi.c"

void write_track1(FILE *file);
void write_track2(FILE *file);

int main(int argc, char **argv)
{
    FILE *midi_file = fopen("demo.mid", "wb");
    MIDI_write_global_header(midi_file, 1, 2, BLACK);
    write_track1(midi_file);
    write_track2(midi_file);
    fclose(midi_file);
}

void write_track1(FILE *file)
{
    unsigned long marque = MIDI_write_track_header(file);
    MIDI_tempo(file, 500000);
    MIDI_fin_de_la_piste(file);
    ecrire_taille_finale_piste(file, marque);
}

void write_track2(FILE *fichier)
{
    unsigned long marque = MIDI_write_track_header(fichier);

    MIDI_Program_Change(fichier, 0, 90);

    for (int i = C3; i <= C3 + 12; i = i + 1)
    {
        Note_unique_avec_duree(fichier, 0, i, 64, BLACK / 2);
    }
    for (int i = 0; i <= 127; i = i + 1)
    {
        MIDI_Program_Change(fichier, 0, i);
        Note_unique_avec_duree(fichier, 0, C3 + 9, 64, BLACK);
    }
    MIDI_fin_de_la_piste(fichier);
    ecrire_taille_finale_piste(fichier, marque);
}
