# Lettore RTTTL per ESP32 con MicroPython.
# @author Filippo Bilardo
import time

NOTE_MAP = {'c': 0, 'd': 2, 'e': 4, 'f': 5, 'g': 7, 'a': 9, 'b': 11, 'h': 11}


def get_frequency(note, octave):
    if note == 'p':
        return 0
    accidental = 0
    if len(note) == 2:
        accidental = 1 if note[1] == '#' else -1
    midi = (octave + 1) * 12 + NOTE_MAP[note[0]] + accidental
    return int(440 * 2 ** ((midi - 69) / 12) + 0.5)


def parse_rtttl(text):
    """Restituisce titolo e note (nome, ottava, millisecondi); ValueError se errato."""
    parts = text.split(':')
    if len(parts) != 3:
        raise ValueError('ERR RTTTL: servono due due-punti')
    defaults = {'d': 4, 'o': 5, 'b': 120}
    if parts[1].strip():
        for item in parts[1].split(','):
            pair = item.strip().split('=')
            if len(pair) != 2 or pair[0] not in defaults or not pair[1].isdigit():
                raise ValueError('ERR RTTTL: impostazioni')
            defaults[pair[0]] = int(pair[1])
    def valid_duration(d):
        return 1 <= d <= 64 and (d & (d - 1)) == 0
    if not valid_duration(defaults['d']) or not 3 <= defaults['o'] <= 7 or not 25 <= defaults['b'] <= 900:
        raise ValueError('ERR RTTTL: impostazioni fuori intervallo')
    notes = []
    if not parts[2].strip():
        return parts[0], notes
    events = parts[2].split(',')
    if events[-1].strip() == '':
        events.pop()  # Consenti una virgola finale, come nel lettore C++.
    for event in events:
        event = event.strip().lower()
        i = 0
        while i < len(event) and event[i].isdigit():
            i += 1
        duration = int(event[:i]) if i else defaults['d']
        if not valid_duration(duration) or i == len(event):
            raise ValueError('ERR RTTTL: durata o nota')
        note = event[i]
        i += 1
        if note not in NOTE_MAP and note != 'p':
            raise ValueError('ERR RTTTL: nota')
        if i < len(event) and event[i] in '#b':
            if note == 'p':
                raise ValueError('ERR RTTTL: alterazione della pausa')
            note += event[i]
            i += 1
        dotted = i < len(event) and event[i] == '.'
        if dotted:
            i += 1
        octave = defaults['o']
        if i < len(event) and event[i].isdigit():
            octave = int(event[i])
            i += 1
        if i < len(event) and event[i] == '.':
            if dotted:
                raise ValueError('ERR RTTTL: due punti di valore')
            dotted = True
            i += 1
        if i != len(event) or not 3 <= octave <= 7:
            raise ValueError('ERR RTTTL: ottava o caratteri residui')
        ms = (240000 // defaults['b']) // duration
        if dotted:
            ms = ms * 3 // 2
        notes.append((note, octave, ms))
    return parts[0], notes


def play_rtttl(text, buzzer):
    name, notes = parse_rtttl(text)
    print('Riproduzione:', name)
    try:
        for note, octave, ms in notes:
            frequency = get_frequency(note, octave)
            buzzer.duty_u16(0)
            if frequency:
                buzzer.freq(frequency)
                buzzer.duty_u16(32768)
                on = ms * 9 // 10
                time.sleep_ms(on)
                buzzer.duty_u16(0)
                time.sleep_ms(ms - on)
            else:
                time.sleep_ms(ms)
    finally:
        buzzer.duty_u16(0)

star_wars = "StarWars:d=4,o=5,b=120:8f,8f,8f,2a#.,2f.6,8d#6,8d6,8c6,2a#.6,f.6,8d#6,8d6,8c6,2a#.6,f.6,8d#6,8d6,8d#6,2c6"
mario = "Super Mario:d=4,o=5,b=100:16e6,16e6,32p,8e6,16c6,8e6,8g6,8p,8g,8p,8c6,16p,8g,16p,8e,16p,8a,8b,16a#,8a,16g.,16e6,16g6,8a6,16f6,8g6,8e6,16c6,16d6,8b,16p,8c6,16p,8g,16p,8e,16p,8a,8b,16a#,8a,16g.,16e6,16g6,8a6,16f6,8g6,8e6,16c6,16d6,8b"
tetris = "Tetris:d=4,o=5,b=160:e6,8b,8c6,8d6,16e6,16d6,8c6,8b,a,8a,8c6,e6,8d6,8c6,b,8b,8c6,d6,e6,c6,a,2a,8p,d6,8f6,a6,8g6,8f6,e6,8e6,8c6,e6,8d6,8c6,b,8b,8c6,d6,e6,c6,a,a"


def main():
    from machine import Pin, PWM
    buzzer = PWM(Pin(27), freq=440, duty_u16=0)
    try:
        for melody in (mario, star_wars, tetris):
            play_rtttl(melody, buzzer)
            time.sleep_ms(1000)
    finally:
        buzzer.duty_u16(0)
        buzzer.deinit()


if __name__ == '__main__':
    main()
