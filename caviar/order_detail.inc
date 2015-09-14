<?php
// VL150705
    /*
     * called from the view for the order details
     * $view: The view object.
            $handler: The handler object.
            $static: A variable that can be used to store reusable data per row.
            $row: Contains the retrieved record from the database per row.
            $row->order_id: Commerce Line Item: Order ID
            $row->line_item_id: Commerce Line Item: Line item ID
            $row->type: Commerce Line Item: Type
            $row->line_item_title: Commerce Line Item: Title
            $row->nothing: Global: Custom text
            $row->field_persons: Commerce Line item: Persons
            $row->line_item_label: Commerce Line Item: Label
            $row->commerce_unit_price: Commerce Line item: Unit price
            $row->quantity: Commerce Line Item: Quantity
            $row->commerce_total: Commerce Line item: Total
            $row->php: Global: PHP
            $data: Contains the retrieved record from the database for all rows.
            $value: Value of this field.
    The debug of the code to be done from sites/all/modules/views_php/plugins/views/views_php_handler_field.inc l 131
    this will be included in the view php code by means of:
    module_load_include('inc', 'caviar', 'order_detail');
     */
function display_caviar_grid($row)
{
    global $user;
    // loads the names of platres and the days f the week
    $myfile = fopen("http://belayaikra.ru/sites/all/modules/caviar/cavgrid.txt", "r") or die("Unable to open
    file!");
    $aa = fgets($myfile);
    $aa = fgets($myfile);
    $aa = fgets($myfile);
    $aa = rtrim($aa);
    $plats = explode(',', $aa);
    $aa = fgets($myfile);
    $aa = fgets($myfile);
    $aa = rtrim($aa);
    $jours = explode(',', $aa);


    $user_data = user_load($user->uid);
    $lid = $row->line_item_id;
    $lineitem = commerce_line_item_load($row->line_item_id); // please check if $lineitem is the same as $row
    $grid = '<table class="footable"><thead><tr><th>Заголовок</th><th>Персоны</th><th>Цена</th><th>Итого</th></tr></thead>';
    $grid .='<tbody><tr><td>'.$row->line_item_title.'</td><td>'.$row->field_persons.'</td>';
    $grid .='<td>'.$row->commerce_unit_price.'</td><td>'.$row->commerce_total.'</td></tr></tbody></table>';
    if ($row->line_item_label == '(GRID)') {
        $grid .= '<table border="1">';
        $grid .= '<tr><th colspan="6">Продукт: ' . $row->type . ' Люди: '
            . $row->field_persons . '</th></tr>';
        $keus = explode('_', $lineitem->field_grdist['und'][0]['value']);
        $choix = array();

        for ($i = 0; $i < sizeof($plats); $i++) {
            $choix[] = explode(',', $keus[$i]);
        }
        $grid .= '<TR><th></th>';
        for ($k = 0; $k < sizeof($plats); $k++) {
            $grid .= '<Th>' . $plats[$k] . '</th>';
        }
        $grid .= '</TR>';

        for ($j = 0; $j < 5; $j++) {
            $grid .= '<TR>';
            $grid .= '<Td>' . $jours[$j] . '</td>';
            for ($k = 0; $k < sizeof($plats); $k++) {
                $grid .= '<Td>' . $choix[$j][$k] . '</td>';
            }
            $grid .= '</TR>';
        }


        $grid .= '</table>';

    }
    return $grid;
}
?>

