<!--
/**
 * COmanage Registry SSH Keys Fields
 *
 * Copyright (C) 2014 University Corporation for Advanced Internet Development, Inc.
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
 * @copyright     Copyright (C) 2014 University Corporation for Advanced Internet Development, Inc.
 * @link          http://www.internet2.edu/comanage COmanage Project
 * @package       registry
 * @since         COmanage Registry v0.9
 * @license       Apache License, Version 2.0 (http://www.apache.org/licenses/LICENSE-2.0)
 * @version       $Id$
 */
-->
<?php
  // Determine if fields are editable
  $e = false;
  
  if(($this->action == "add" && $permissions['add']) || ($this->action == "edit" && $permissions['edit']))
    $e = true;
    
  // We shouldn't get here if we don't have at least read permission, but check just in case
  
  if(!$e && !$permissions['view'])
    return(false);
  
  // Migrate the target person from a named argument to a form field
  if(isset($this->request->params['named']['copersonid']))
    print $this->Form->hidden('co_person_id', array('default' => Sanitize::html($this->request->params['named']['copersonid']))) . "\n";
  elseif(isset($this->request->data['SshKey']['co_person_id']))
    print $this->Form->hidden('co_person_id', array('default' => Sanitize::html($this->request->data['SshKey']['co_person_id']))) . "\n";
?>
<table id="<?php print $this->action; ?>_ssh_key" class="ui-widget">
  <tbody>
    <tr class="line1">
      <td>
        <?php print _txt('fd.sshkey.comment'); ?>
      </td>
      <td>
        <?php print ($e ? $this->Form->input('comment', array('class' => 'focusFirst')) : Sanitize::html($ssh_keys[0]['SshKey']['comment'])); ?>
      </td>
    </tr>
    <tr class="line2">
      <td>
        <?php print _txt('fd.sshkey.type'); ?>
      </td>
      <td>
        <?php
          global $cm_lang, $cm_texts;
          $attrs['value'] = (isset($ssh_keys) ? $ssh_keys[0]['SshKey']['type'] : SshKeyTypeEnum::DSA);
          $attrs['empty'] = false;
          
          if($e) {
            print $this->Form->select('type',
                                      $cm_texts[ $cm_lang ]['en.sshkey.type'],
                                      $attrs);
            
            if($this->Form->isFieldError('type')) {
              print $this->Form->error('type');
            }
          } else {
            print Sanitize::html($contact_t[ $ssh_keys[0]['SshKey']['type'] ]);
          }
        ?>
      </td>
    </tr>
    <tr class="line1">
      <td>
        <?php print _txt('fd.sshkey.skey'); ?>
      </td>
      <td>
        <?php print ($e
                     ? $this->Form->input('skey')
                     : Sanitize::html($ssh_keys[0]['SshKey']['skey'])); ?>
      </td>
    </tr>
    <tr>
      <td>
        <i><span class="required"><?php echo _txt('fd.req'); ?></span></i><br />
      </td>
      <td>
        <?php
          if($e) {
            print $this->Form->submit($submit_label);
            print $this->Form->button(_txt('op.reset'), 
                                      array('type'=>'reset'));
          }
        ?>
      </td>
    </tr>
  </tbody>
</table>
<?php if($this->action == 'add'): ?>
<hr />
<h2><?php print _txt('op.upload.new', array(_txt('ct.ssh_keys.1'))); ?></h2>

<table id="<?php print $this->action; ?>_ssh_key_upload" class="ui-widget">
  <tbody>
    <tr class="line1">
      <td>
        <?php
          // Close the previous form
          print $this->Form->end();
          
          // Start a new form (this will get closed by Standard/add/edit.ctp)
          print $this->Form->create('SshKey', array('type' => 'file',
                                                    'action' => 'addKeyFile'));
          
          // Since we started a new form, we need to re-insert the coperson id
          
          if(isset($this->request->params['named']['copersonid']))
            print $this->Form->hidden('co_person_id', array('default' => Sanitize::html($this->request->params['named']['copersonid']))) . "\n";
          elseif(isset($this->request->data['SshKey']['co_person_id']))
            print $this->Form->hidden('co_person_id', array('default' => Sanitize::html($this->request->data['SshKey']['co_person_id']))) . "\n";
          
          print $this->Form->file('SshKey.keyFile');
        ?>
      </td>
    </tr>
    <tr>
      <td>
        <?php
          if($e) {
            print $this->Form->submit(_txt('op.upload'));
          }
        ?>
      </td>
    </tr>
  </tbody>
</table>
<?php endif; // add ?>