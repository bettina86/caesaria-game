g_config.gods = {
  ceres : "ceres",
  mars : "mars",
  neptune : "neptune",
  venus : "venus",
  mercury : "mercury"
}

g_config.festival = {
  small :  { id:1, limiter:20, minCost : 10, title:"small_festival" },
  middle : { id:2, limiter:10, minCost : 20, title:"middle_festival"},
  big :    { id:3, limiter:5,  minCost : 50,  title:"big_festival"},
  great :  { id:4, limiter:3,  minCost : 100, title:"great_festival", wineLimiter:250}
}

g_config.religion.gods_config = [
  { id: g_config.gods.ceres,   name : "Ceres",   service : "srvc_religionCeres",   image:  "panelwindows_00017" },
  { id: g_config.gods.mars,    name : "Mars",    service : "srvc_religionMars",    image : "panelwindows_00020" },
  { id: g_config.gods.neptune, name : "Neptune", service : "srvc_religionNeptune", image : "panelwindows_00018" },
  { id: g_config.gods.venus,   name : "Venus",	 service : "srvc_religionVenus",   image : "panelwindows_00021"	},
  { id: g_config.gods.mercury, name : "Mercury", service : "srvc_religionMercury", image : "panelwindows_00019" }
]
