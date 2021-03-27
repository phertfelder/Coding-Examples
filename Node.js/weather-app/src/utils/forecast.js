const request = require("request")

const forecast = (latitude, longitude, callback) => {
  const url =
    "http://api.weatherstack.com/current?access_key=249b16968af0e36c34cab594e7080295&query=" +
    latitude +
    "," +
    longitude +
    "&units=f"

  request({ url, json: true }, (error, { body }) => {
    if (error) {
      callback("Unable to connect to weather service!", undefined)
    } else if (body.error) {
      callback("Unable to find location", undefined)
    } else {
      callback(
        undefined,
        // Current_Conditions:response.body.current.weather_descriptions[0],
        // CurrentTemp:response.body.current.temperature,
        // FeelsLike:response.body.current.feelslike
        body.current.weather_descriptions[0] +
          ". It is currently " +
          body.current.temperature +
          " degrees out. It feels like " +
          body.current.feelslike +
          " degrees out."
      )
    }
  })
}
module.exports = forecast
