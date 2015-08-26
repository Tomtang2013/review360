<?php

/**
 * @file
 * The PHP page that serves all page requests on a Drupal installation.
 *
 * The routines here dispatch control to the appropriate handler, which then
 * prints the appropriate page.
 *
 * All Drupal code is released under the GNU General Public License.
 * See COPYRIGHT.txt and LICENSE.txt.
 */

/**
 * Root directory of Drupal installation.
 */
define('DRUPAL_ROOT', getcwd());

function dd($data){
    $fileP2 = 'E://websitedata//wwwzigonlinecn_2lwd02fk//www//review360//sites//default//files//temp//drupal_debug.txt';
    $fileP1 = $file = 'c://wamp//tmp//drupal_debug.txt';
      ob_start();
      print_r($data);
      $string = ob_get_clean();
      $string .= "\n";
      $file = $fileP1;
      file_put_contents($file, $string,8);
 }
 
require_once DRUPAL_ROOT . '/includes/bootstrap.inc';
drupal_bootstrap(DRUPAL_BOOTSTRAP_FULL);
menu_execute_active_handler();
