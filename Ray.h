//#pragma once
//class Ray
//{
//	Ray() {
//		sf::Vertex line[] ={
//			sf::Vertex(sf::Vector2f(10, 10)),
//			sf::Vertex(sf::Vector2f(150, 150))
//		}
//	}
//
//};
//bool check_point_ray(float x, float y, float xray, float yray, Player & player) {
//    if (player.GetPosition().x >= xray) {
//        if (player.GetPosition().y >= yray) {
//            if (xray <= x <= player.GetPosition().x and yray <= y <= player.GetPosition().y)
//                return true;
//            return false;
//        }
//        else
//        {
//            if (xray <= x <= player.GetPosition().x and yray >= y >= player.GetPosition().y)
//                return true;
//            return false;
//        }
//    }
//    else {
  //      if (player.GetPosition().y >= yray) {
 //           if (xray >= x >= player.GetPosition().x and yray <= y <= player.GetPosition().y)
  //              return true;
  //          return false;
  //      }
 //       else
//        {
 //           if (xray >= x >= player.GetPosition().x and yray >= y >= player.GetPosition().y)
 //               return true;
 //           return false;
 //       }
//    }
//}

//CYCLE
        //for (int i = 0; i <= 10; i ++){
        //    sf::Vector2f ray_coords(player.GetPosition().x + naxod(player, s, i), player.GetPosition().y - cos((player.GetAngle() + i) * 3.14159 / 180) * s);
        //    double x1 = 150, y1 = 150, x2 = 200, y2 = 200, x3 = player.GetPosition().x, y3 = player.GetPosition().y, x4 = ray_coords.x, y4 = ray_coords.y;
        //    double a1, a2, b1, b2, c1, c2;
        //    a1 = y1 - y2;
        //    b1 = x2 - x1;
        //    c1 = x1 * y2 - x2 * y1;
        //    a2 = y3 - y4;
        //    b2 = x4 - x3;
        //    c2 = x3 * y4 - x4 * y3;
        //    intersect(a1, a2, b1, b2, c1, c2, x, y);
        //    

        //    if (check(player, ray_coords, x, y)) {
        //        if (lenght(ray_coords.x, ray_coords.y, player) >= lenght(x, y, player))
        //            ray_coords = sf::Vector2f(float(x), float(y));
        //    }
        //    printf("%f %f \n", ray_coords.x, ray_coords.y);
        //    sf::Vertex line[] =
        //    {
        //        sf::Vertex(player.GetPosition()),
        //        sf::Vertex(ray_coords)

        //    };
        //    abs(window, player, ray_coords);

        //    break;
        //}
        //abs(window, player, ray_coords);