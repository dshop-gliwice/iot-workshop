
TOKEN_URL='https://api.yaas.io/hybris/oauth2/v1/token'
DATA_URL='https://api.yaas.io/hybris/document/v1/iotexp/iotexp.demoapp/data/<DEVICE>?sort=metadata.createdAt:desc&pageSize=100'

var app = {}

$( document ).ready(function() {
  $( "#form-settings" ).sisyphus();
  initChart()

  $('#btnGetToken').on('click', function(event) {
    event.preventDefault();
    getToken($("#client-id").val(), $("#client-secret").val())
  });
});

function initChart(){
  app.chart = c3.generate({
    bindto: '#chart',
    data: {
        x: 'x',
        columns: [
            ['x'],
            ['temperature'],
            ['humidity']
        ],
        axes: {
            temperature: 'y',
            humidity: 'y2'
        },
        colors: {
          'temperature': '#ff0000',
          'humidity': '#0000ff'
        }
    },
    axis: {
      x: {
        type: 'timeseries',
        tick: {
          count: 6,
          format: '%Y-%m-%d %H:%M:%S'
        }
      },
      y: {
        label: {
          text: 'Temperature',
          position: 'outer-middle'
        }
        //max: 30,
        //min: 0,
      },
      y2: {
        label: {
          text: 'Humidity',
          position: 'outer-middle'
        },
        //max: 100,
        //min: 20,
        show: true
      }
    }
  });
}

function getData(){
  url = DATA_URL.replace("<DEVICE>", $("#device").val())
  $.ajax({
    dataType: "json",
    headers: {
      'Authorization': 'Bearer ' + app.token
    },
    url: url,
    success: function( data ) {
      updateChart(data)
      $.notify("Data loaded!", "success");
    },
    error: function (xhr, ajaxOptions, thrownError) {
      $.notify("getData error: " + xhr.responseJSON.message, "error");
    }
  });
}

function getToken(clientID, clientSecret){
  $.ajax({
    url: TOKEN_URL,
    type: 'post',
    data: {
        client_id: clientID,
        client_secret: clientSecret,
        scope: 'hybris.document_view hybris.document_manage',
        grant_type: 'client_credentials'
    },
    dataType: 'json',
    contentType: 'application/x-www-form-urlencoded',
    success: function (data) {
        app.token = data.access_token
        $.notify("Authorization successful", "success");
        getData()
    },
    error: function (xhr, ajaxOptions, thrownError) {
      $.notify("getToken error: " + xhr.responseJSON.error +
          "\n Description: " + xhr.responseJSON.error_description, "error");
    }
  });
}

function updateChart(data){
  xArray = ["x"]
  tempArray = ["temperature"]
  humArray = ["humidity"]

  $.each( data, function( key, val ) {
    xArray.push(new Date(val.metadata.createdAt))
    tempArray.push(val.temperature)
    humArray.push(val.humidity)
    console.log(val.temperature)
  });
  app.chart.load({
    columns: [
      xArray,
      tempArray,
      humArray
    ]
  })
}

