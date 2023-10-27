const soundFiles = [
    new Howl({ src: ['assets/audio/maintheme.wav'], preload: true, autoplay: true, loop: true, volume: 0.5 }),
	new Howl({ src: ['assets/audio/heartbeat.wav'], preload: true, loop: true }),
	new Howl({ src: ['assets/audio/open.wav'], preload: true }),
    new Howl({ src: ['assets/audio/close.wav'], preload: true }),
];
