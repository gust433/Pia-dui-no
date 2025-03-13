from serial import Serial
import pygame
from threading import Thread

pygame.mixer.init()

Note = {'NoteRE' : 'note_re2.wav',
        'NoteDO' : 'C4.wav',
        'NoteMI' : 'E4.wav',
        'NoteFA' : 'F4.wav',
        'NoteSOL' : 'G4.wav',
        'NoteLA' : 'A4.wav',
        'NoteSI' : 'B4.wav',
        'c#' : 'c4#2.wav',
        'd#' : 'd4#2.wav',
        'f#' : 'f4#2.wav',
        'g#' : 'g4#2.wav',
        'a#' : 'a4#2.wav'}
ser = Serial('COM4',115200, timeout=1)

note_sound = {key: pygame.mixer.Sound(value) for key, value in Note.items()}

def play_sound_thread(sound):
    sound.play()

    
while True:
    if ser.in_waiting>0:
        message = ser.readline().decode('utf-8').strip()
        if message in note_sound:
            Thread(target=play_sound_thread, args=(note_sound[message],), daemon=True).start()
