{
  /*notes_action : { acNone : 0, acMove : 1, acFight : 2, acDie : 3, acWork : 4 }*/

  citizen : {
    move : { rc : "citizen01", start : 1, frames : 12, action : 1, step : 8 }
  }

  recruter : {
    move : { rc : "citizen01", start : 1, frames : 12, action : 1, step : 8 }
  }

  etruscanSoldier : {
    move : { rc : "etruscan", start : 249, frames : 12, action : 1, step : 8 }
    fight : { rc : "etruscan", start : 345, frames : 6, action : 2, step : 8 }
    die : { rc : "etruscan", start : 393, frames : 8, action : 3, step : 0 }
  }

  etruscanArcher : {
    move : { rc : "etruscan", start : 401, frames : 12, action : 1, step : 8 }
    fight : { rc : "etruscan", start : 497, frames : 6, action : 2, step : 8 }
    die : { rc : "etruscan", start : 593, frames : 8, action : 3, step : 0 }
  }

  bathlady : {
    move : { rc : "citizen01", start : 105, frames : 12, action : 1, step : 8 }
  }

  priest : {
    move : { rc : "citizen01", start : 209, frames : 12, action : 1, step : 8 }
  }

  actor : {
    move : { rc : "citizen01", start : 313, frames : 12, action : 1, step : 8 }
  }

  lionTamer : {
    move : { rc : "citizen01", start : 417, frames : 12, action : 1, step : 8 }
  }

  circusCharioter : {
    move : { rc : "carts", start : 537, frames : 8, action : 1, step : 8 }
  }

  taxCollector : {
    move : { rc : "citizen01", start : 617, frames : 12, action : 1, step : 8 }
  }

  scholar : {
    move : { rc : "citizen01", start : 721, frames : 12, action : 1, step : 8 }
  }

  marketLady : {
    move : { rc : "citizen01", start : 825, frames : 12, action : 1, step : 8 }
  }

  marketBuyer : {
    move : { rc : "citizen01", start : 825, frames : 12, action : 1, step : 8 }
  }

  cartPusher : {
    none : { rc : "citizen01", start : 929, frames : 1, action : 0, step : 8 }
    move : { rc : "citizen01", start : 929, frames : 12, action : 1, step : 8 }
  }

  supplier : {
    move : { rc : "citizen01", start : 929, frames : 12, action : 1, step : 8 }
  }

  immigrant :
    move : { rc : "citizen01", start : 1033, frames : 12, action : 1, step : 8 }
  }

  engineer : {
    move : { rc : "citizen01", start : 1137, frames : 12, action : 1, step : 8 }
  }

  gladiator : {
    move : { rc : "citizen02", start : 1, frames : 12, action : 1, step : 8 }
  }

  /*
  gladiator2 : {
    move : { rc : "citizen02", start : 199, frames : 12, action : 1, step : 8 }
  }
  */

  protestor : {
    move : { rc : "citizen02", start : 351, frames : 12, action : 1, step : 8 }
  }

  mugger : {
    move : { rc : "citizen02", start : 351, frames : 12, action : 1, step : 8 }
  }

  rioter : {
    move : { rc : "citizen02", start : 351, frames : 12, action : 1, step : 8 }
  }

  indigeneRioter : {
    move : { rc : "citizen02", start : 351, frames : 12, action : 1, step : 8 }
  }

  barber : {
    move : { rc : "citizen02", start : 463, frames : 12, action : 1, step : 8 }
  }

  prefect : {
    /* notes : { dragWater : 6, fightFire : 7 } */
    move : { rc : "citizen02", start : 615, frames : 12, action : 1, step : 8 }
    dragWater : { rc : "citizen02", start : 767, frames : 12, action : 6, step : 8 }
    fightFire : { rc : "citizen02", start : 863, frames : 6, action : 7, step : 8, delay : 3 }
    fight : { rc : "citizen02", start : 719, frames : 6, action : 2, step : 8 }
  }

  emigrant : {
    move : { rc : "citizen02", start : 911, frames : 12, action : 1, step : 8 }
    sit : { rc : "citizen02", start : 1015, frames : 1, action : 0, step : 8 }
  }

  doctor : {
    move : { rc : "citizen03", start : 817, frames : 12, action : 1, step : 8 }
  }

  patrician : {
    move : { rc : "citizen03", start : 713, frames : 12, action : 1, step : 8 }
  }
  /*
  patrician2 : {
    move : { rc : "citizen03", start : 921, frames : 12, action : 1, step : 8 }
  }
  */

  teacher : {
    move : { rc : "citizen03", start : 1025, frames : 12, action : 1, step : 8 }
  }

  soldier : {
    move : { rc : "citizen03", start : 97, frames : 12, action : 1, step : 8 }
  }

  /*
  javelineer : {
    move : { rc : "citizen03", start : 241, frames : 12, action : 1, step : 8 }
  }
  */

  romeHorseman : {
    move : { rc : "citizen04", start : 1, frames : 12, action : 1, step : 8 }
    fight : { rc : "citizen04", start : 97, frames : 6, action : 2, step : 8 }
    die : { rc : "citizen04", start : 144, frames : 8, action : 3, step : 0 }
  }

  merchant : {
    move : { rc : "carts", start : 145, frames : 5, action : 1, step : 8 }
  }

  merchantCamel : {
    move : { rc : "carts", start : 145, frames : 5, action : 1, step : 8 }
  }

  /*
  camelMerchant : {
    move : { rc : "carts", start : 273, frames : 12, action : 1, step : 8 }
  }
  */

  marketKid : {
    move : { rc : "carts", start : 369, frames : 12, action : 1, step : 8 }
  }

  sheep : {
    move : { rc : "citizen04", start : 153, frames : 6, action : 1, step : 8, delay : 2 }
    sit : { rc : "citizen04", start : 249, frames : 1, action : 0, step : 8 }
    die : { rc : "citizen04", start : 257, frames : 8, action : 3, step : 0 }
  }

  zebra : {
    move : { rc : "citizen04", start : 425, frames : 12, action : 1, step : 8 }
    sit : { rc : "citizen04", start : 529, frames : 5, action : 0, step : 8 }
    die : { rc : "citizen04", start : 520, frames : 8, action : 3, step : 0 }
  }

  wolf : {
    move : { rc : "citizen04", start : 265, frames : 12, action : 1, step : 8 }
    fight : { rc : "citizen04", start : 369, frames : 7, action : 2, step : 8 }
    die : { rc : "citizen04", start : 361, frames : 8, action : 3, step : 0 }
  }

  fishingBoat : {
    move : { rc : "carts", start : 249, frames : 1, action : 1, step : 8 }
    work : { rc : "carts", start : 257, frames : 1, action : 4, step : 8 }
    die : { rc : "carts", start : 265, frames : 8, action : 3, step : 0 }
  }

  lion : {
    move : { rc : "citizen03", start : 1, frames : 12, action : 1, step : 8 }
  }

  charioteer : {
    move : { rc : "citizen05", start : 1, frames : 12, action : 1, step : 8 }
  }

  britonSoldier : {
    move : { rc : "celts", start : 249, frames : 12, action : 1, step : 8 }
    fight : { rc : "celts", start : 345, frames : 6, action : 3, step : 8 }
  }

  legionary : {
    move : { rc : "citizen03", start : 553, frames : 12, action : 1, step : 8 }
    fight : { rc : "citizen03", start : 649, frames : 6, action : 3, step : 8 }
  }

  romeGuard : {
    move : { rc : "citizen03", start : 97, frames : 12, action : 1, step : 8 }
    fight : { rc : "citizen03", start : 192, frames : 6, action : 3, step : 8 }
    die : { rc : "citizen03", start : 232, frames : 1, action : 3, step : 0 }
  }

  romeSpearman : {
    move : { rc : "citizen03", start : 241, frames : 12, action : 1, step : 8 }
    fight : { rc : "citizen03", start : 337, frames : 6, action : 2, step : 8 }
    die : { rc : "citizen03", start : 385, frames : 8, action : 3, step : 0 }
  }

  missioner : {
    move : { rc : "citizen03", start : 921, frames : 12, action : 1, step : 8 }
    die : { rc : "citizen03", start : 1016, frames : 1, action : 3, step : 0 }
  }

  seaMerchant : {
    move : { rc : "carts", start : 241, frames : 1, action : 1, step : 8 }
    die       : { rc : "carts", start : 265, frames : 8, action : 3, step : 0 }
  }

  indigene : {
    move   : { rc : "indigene", start : 1, frames : 12, action : 1, step : 8 }
  }

  balista : {
    none  : { rc : "sprites", start : 210, frames : 1, action : 0, step : 8 }
    fight : { rc : "sprites", start : 162, frames : 6, action : 2, step : 8 }
    work  : { rc : "sprites", start : 162, frames : 6, action : 4, step : 8 }
  }

  romeChastenerSoldier : {
    move : { rc : "citizen03", start : 441, frames : 12, action : 1, step : 8 }
    fight : { rc : "citizen03", start : 393, frames : 6, action : 2, step : 8, delay : 2 }
    die : { rc : "citizen03", start : 545, frames : 8, action : 3, step : 0 }
  }

  romeChastenerElephant : {
    move : { rc : "carthegenians", start : 401, frames : 12, action : 1, step : 8 }
    /*fight : { rc : "carthegenians", start : 497, frames : 1, action : 2, step : 8 }*/
    die : { rc : "carthegenians", start : 505, frames : 8, action : 3, step : 0 }
  }
}

