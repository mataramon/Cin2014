#include "init.h"
#include "ui_init.h"
#include <QFile>

Init::Init(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Init)
{
    ui->setupUi(this);
    ui->webView->load(QUrl::fromLocalFile("file:///C:/Users/Angel/UIDesk/maps.html"));
    ui->webView->setHtml("<html> \
                          <head> \
                             <link rel=\"stylesheet\" href=\"http://cdn.leafletjs.com/leaflet-0.7.3/leaflet.css\" /> \
                             <script src=\"http://cdn.leafletjs.com/leaflet-0.7.3/leaflet.js\"></script> \
                             <style type=\"text/css\"> \
                                 #map { width:900px;  height:500px; } \
                             </style> \
                             <!-- Java scripts items --> \
                             <script type=\"text/javascript\"> \
                                 window.onload = function () { \
                                     var map = L.map('map').setView([20.6667,-103.5000], 10); \
                                     L.tileLayer('http://{s}.tile.osm.org/{z}/{x}/{y}.png', { \
                                                   attribution: '&copy; <a href=\"http://osm.org/copyright\">OpenStreetMap</a> contributors' \
                                                 }).addTo(map); \
                                      L.marker([20.6665,-103.5005]).addTo(map).bindPopup('No se donde estamos').openPopup(); \
                                 }; \
                             </script> \
                         </head> \
                         <body> \
                      <div id=\"map\"></div> \
                         </body> \
                     </html>");
}

Init::~Init()
{
    delete ui;
}
