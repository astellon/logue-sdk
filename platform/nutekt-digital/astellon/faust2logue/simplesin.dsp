import("stdfaust.lib");

frequency = hslider("frequency", 440, 0, 5000, 0.001);

process = os.oscs(frequency);