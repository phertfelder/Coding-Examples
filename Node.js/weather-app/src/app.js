const express = require("express")
const path = require("path")
const hbs = require("hbs")
const app = express()
const geocode = require("./utils/geocode")
const forecast = require("./utils/forecast")

// Define paths for Express config
const publicDirectoryPath = path.join(__dirname, "../public")
const viewsPath = path.join(__dirname, "../templates/views")
const partialspath = path.join(__dirname, "../templates/partials")

//Setup handlebars engine and views location
app.set("view engine", "hbs")
app.set("views", viewsPath)
hbs.registerPartials(partialspath)

//Setup static directory to server
app.use(express.static(publicDirectoryPath))

app.get("", (req, res) => {
  res.render("index", {
    title: "Weather App",
    name: "Paul H",
  })
})
app.get("/about", (req, res) => {
  res.render("about", {
    title: "About Me",
    name: "Paul H",
  })
})
app.get("/help", (req, res) => {
  res.render("help", {
    message: "If help is needed email me at: ",
    email: "paulhertfelder@gmail.com",
    title: "Help",
    name: "Paul H",
  })
})

app.get("/weather", (req, res) => {
  if (!req.query.address) {
    return res.send({
      error: "You must provide an address",
    })
  }

  geocode(
    req.query.address,
    (error, { latitude, longitude, location } = {}) => {
      if (error) {
        return res.send({
          error: error,
        })
      }

      forecast(latitude, longitude, (error, forecastData) => {
        if (error) {
          return res.send({
            error: error,
          })
        }
        res.send({
          forecast: forecastData,
          location,
          address: req.query.address,
        })
      })
    }
  )
})

app.get("/help/*", (req, res) => {
  res.render("404", {
    title: "404",
    name: "Paul H",
    message: "Help article not found.",
  })
})

app.get("/products", (req, res) => {
  if (!req.query.search) {
    return res.send({
      error: "You must provide a search term.",
    })
  }

  console.log(req.query.search)
  res.send({
    products: [],
  })
})

//Let this be at bottom of app.get's
app.get("*", (req, res) => {
  return res.render("404", {
    title: "404",
    name: "Paul H",
    message: "Page not Found.",
  })
})

app.listen(3000, () => {
  console.log("Server is up on port 3000")
})
