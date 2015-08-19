<!--
/**
 * COmanage Registry CO Enrollment Configuration Fields
 *
 * Copyright (C) 2015 University Corporation for Advanced Internet Development, Inc.
 *
 * Licensed under the Apache License, Version 2.0 (the "License"); you may not use this file except in compliance with
 * the License. You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software distributed under
 * the License is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY
 * KIND, either express or implied. See the License for the specific language governing
 * permissions and limitations under the License.
 *
 * @copyright     Copyright (C) 2011-15 University Corporation for Advanced Internet Development, Inc.
 * @link          http://www.internet2.edu/comanage COmanage Project
 * @package       registry
 * @since         COmanage Registry v0.3
 * @license       Apache License, Version 2.0 (http://www.apache.org/licenses/LICENSE-2.0)
 * @version       $Id$
 */
-->
<?php
// Add buttons
if($this->action != "add") {

  // If status is pending confirmation, offer a link to resend the invite
  if($permissions['resend']
    && !empty($co_petitions[0]['CoPetition']['status'])
    && $co_petitions[0]['CoPetition']['status'] == PetitionStatusEnum::PendingConfirmation) {

    $buttonUrl = array(
      'controller'    => 'co_petitions',
      'action'        => 'resend',
      $co_petitions[0]['CoPetition']['id']
    );

    // Construct jQuery popup
    $onclickAction =  "javascript:js_confirm_generic('" .
                      _txt('op.inv.resend.confirm', array(generateCn($co_petitions[0]['EnrolleeCoPerson']['PrimaryName']))) .
                      "', '" . Router::url($buttonUrl) . "', '" .
                      _txt('op.inv.resend') . "');
                      return false;";

    $params['topLinks'][] = $this->Html->link(
      _txt('op.inv.resend'),
      $buttonUrl,
      array(
        'class' => 'invitebutton',
        'onclick' => $onclickAction
      )
    );
  }

  if($permissions['edit']) {
    $params['topLinks'][] = $this->Html->link(
      _txt('op.petition.comment'),
      array(
        'controller'    => 'co_petition_history_records',
        'action'        => 'add',
        'copetitionid'  => $co_petitions[0]['CoPetition']['id']
      ),
      array(
        'class' => 'notebutton'
      )
    );
  }

  // If status is pending confirmation or approval, offer ability to flag as duplicate.
  if($permissions['dupe']
    && !empty($co_petitions[0]['CoPetition']['status'])
    && ($co_petitions[0]['CoPetition']['status'] == PetitionStatusEnum::PendingApproval
      || $co_petitions[0]['CoPetition']['status'] == PetitionStatusEnum::PendingConfirmation)) {

    $buttonUrl = array(
      'controller'    => 'co_petitions',
      'action'        => 'dupe',
      $co_petitions[0]['CoPetition']['id']
    );

    // Construct jQuery popup
    $onclickAction =  "javascript:js_confirm_generic('" .
                      _txt('op.petition.dupe.confirm') .
                      "', '" . Router::url($buttonUrl) . "', '" .
                      _txt('op.petition.dupe') . "');
                      return false;";

    $params['topLinks'][] = $this->Html->link(
      _txt('op.petition.dupe'),
      $buttonUrl,
      array(
        'class'   => 'flagbutton',
        'onclick' => $onclickAction
      )
    );
  }

  // Add button for related Org Identity
  if(!empty($co_petitions[0]['CoPetition']['enrollee_org_identity_id'])) {
    $params['topLinks'][] = $this->Html->link(
      _txt('ct.org_identities.1'),
      array(
        'controller'    => 'org_identities',
        'action'        => 'view',
        $co_petitions[0]['CoPetition']['enrollee_org_identity_id'],
        'co'            => $co_petitions[0]['CoPetition']['co_id']
      ),
      array(
        'class' => 'contactbutton'
      )
    );
  }

  // Add button for related CO Person
  if(!empty($co_petitions[0]['CoPetition']['enrollee_co_person_id'])) {
    $params['topLinks'][] = $this->Html->link(
      _txt('ct.co_people.1'),
      array(
        'controller'    => 'co_people',
        'action'        => 'canvas',
        $co_petitions[0]['CoPetition']['enrollee_co_person_id']
      ),
      array(
        'class' => 'contactbutton'
      )
    );
  }

}