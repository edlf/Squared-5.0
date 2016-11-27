Pebble.addEventListener('ready', function() {
  console.log('PebbleKit JS ready!');
  console.log('WatchToken '+Pebble.getWatchToken());
});

Pebble.addEventListener('appmessage', function() {
  console.log('got appmessage');
});

Pebble.addEventListener('showConfiguration', function() {
    var url='http://pebble.lastfuture.de/config/squared416/';
    var watch = Pebble.getActiveWatchInfo ? Pebble.getActiveWatchInfo() : null;
    if (watch) {
      url += "?model="+watch.model+"&hardware="+watch.platform;
    }
    console.log('Showing configuration page: '+url);
    Pebble.openURL(url);
});

Pebble.addEventListener('webviewclosed', function(e) {
  var configData = JSON.parse(decodeURIComponent(e.response));
  console.log('Configuration page returned: '+JSON.stringify(configData));
  var options = {
    large_mode: 0+(configData.large_mode === 'true'),
    eu_date: 0+(configData.eu_date === 'true'),
    quick_start: 0+(configData.quick_start === 'true'),
    leading_zero: 0+(configData.leading_zero === 'true'),
    background_color: configData.background_color,
    number_base_color: configData.number_base_color,
    number_variation: configData.number_variation,
    ornament_base_color: configData.ornament_base_color,
    ornament_variation: configData.ornament_variation,
    invert: 0+(configData.invert === 'true'),
    monochrome: 0+(configData.monochrome === 'true'),
    center: 0+(configData.center === 'true'),
    btvibe: 0+(configData.btvibe === 'true'),
    contrast: 0+(configData.contrast === 'true'),
    nightsaver: 0+(configData.nightsaver === 'true'),
    ns_start: parseInt(configData.ns_start),
    ns_stop: parseInt(configData.ns_stop),
    backlight: 0+(configData.backlight === 'true'),
    weekday: 0+(configData.weekday === 'true'),
    bottomrow: parseInt(configData.bottomrow),
    wristflick: parseInt(configData.wristflick),
    stepgoal: parseInt(configData.stepgoal),
    dynamicstepgoal: 0+(configData.dynamicstepgoal === 'true'),
    cheeky: 0+(configData.cheeky === 'true')
  };
  if (configData.background_color) {
    Pebble.sendAppMessage(options, function() {
      console.log('Send successful!');
    }, function() {
      console.log('Send failed!');
    });
  }
});