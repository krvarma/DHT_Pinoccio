// Grab the value element
var tvalue = document.getElementById('tvalue');
var hvalue = document.getElementById('hvalue');

// Initialize the Pinoccio API with a read-only token
// https://docs.pinocc.io/api.html#readonly-token
var api = pinoccioAPI('<<readonly-token>>');

// Initialize the sync stream with {stale:1}
// https://docs.pinocc.io/api.html#realtime-stream-of-changes
var s = api.sync({stale:1});

// When the sync stream gets data
s.on('data', function(data){
  // If it's the value we want, set the value element text
  if (data.type === 'DHT22' && data.troop === '11' && data.scout === '1') {
    tvalue.innerHTML = data.value.t / 100;
    hvalue.innerHTML = data.value.h / 100;
  }
})