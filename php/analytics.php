<?php

if(!isset($_GET['secret']) or (isset($_GET['secret']) and $_GET['secret']!=='41072Monit0r')) die("unauthorized");

ini_set('error_reporting',true);
ini_set('display_errors',true);

require_once (realpath(dirname(__FILE__))).'/google-api-php-client-2.1.3_PHP54/vendor/autoload.php';
$client = new Google_Client();
$client->setApplicationName("Website Monitor");
$client->setAuthConfig(realpath(dirname(__FILE__)).'/Ballystics-5be35395db7b.json');
$client->addScope('https://www.googleapis.com/auth/analytics.readonly');
$analyticsViewId = 'ga:'.$_GET['viewId'];
$analytics = new Google_Service_Analytics($client);
try {
    //$result = $service->data_realtime->get(
    //    $GA_VIEW_ID,
    //    'rt:activeVisitors'
    //);
    //$count = $result->totalsForAllResults['rt:activeVisitors'];
    //echo $count;

    $startDate          = '7daysAgo';//date('Y-m-d',time()-604800);
    $endDate            = date('Y-m-d',time());
    $metrics            = 'ga:pageviews';

    $data = $analytics->data_ga->get($analyticsViewId, $startDate, $endDate, $metrics
        , array(
        'dimensions'    => 'ga:dayOfWeek,ga:date',
        //'filters'       => 'ga:pagePath==/url/to/product/',
        'sort'          => '-ga:date',
    )
    );

// Data
    $items = $data->getRows();
    echo json_encode($items);
} catch(Exception $e) {
    
    echo '<pre>';
    var_dump($e);
    echo '</pre>';
}
